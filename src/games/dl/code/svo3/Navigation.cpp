#include "CInputContextBase.h"
#include "SVTagModule.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_Navigation_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "Navigation.h"
#include "SVTag.h"
#include "TagUtils.h"
#include "CDrawContextBase.h"
#include "CAudioContextBase.h"
#include "CPage.h"

extern "C" {

extern char svoNavigationSource[];
#define SECTION(name) __attribute__((section(".svo_Navigation_" #name)))

SECTION(reset___dupe2) void reset___dupe2(CNavInfoState *navigation)
{
    navigation->right = 0;
    navigation->up = 0;
    navigation->down = 0;
    navigation->left = 0;
}

}

typedef struct { // 0x08
    /* 0x00 */ float x;
    /* 0x04 */ float y;
} tPoint;
extern "C" {
extern char svoNavigationZoneAttribute[];
extern char svoNavigationSoundClass[];
CAudioContextBaseState *GetAudioContext(void);
void setWrapDimensions(int direction, float *x, float *y, float *width, float *height, CInputContextBaseState *input);
int lt_double(double a, double b);
float getDistanceAutoNav(int x, int y, int tx, int ty, int direction, int ignoreZone, int ignoreMult);
}
extern "C" SECTION(autoNavigate) int autoNavigate(SVTag *selected, CInputContextBaseState *input, CDrawContextBase *draw, iks *xml, CPage *page)
{
    tPoint curFrom;
    tPoint curTo;
    tPoint target[5];
    tPoint cur[5];
    SVTag *closest = 0;
    float shortest = 9999.0f;
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    int ignoreZone;
    curFrom.x = -1.0f;
    curFrom.y = -1.0f;
    selected->vtable->GetDimensions(selected, &x, &y, &width, &height);
    int tryWrapMax = 1;
    int tryWrapCnt = 0;
    if (input->vtable->WrapSelections(input)) tryWrapMax = 2;
    for (; tryWrapCnt < tryWrapMax; tryWrapCnt++) {
        int direction;
        if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP) || input->specialKeyCode == 0x81) direction = 0;
        else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN) || input->specialKeyCode == 0x82 || input->specialKeyCode == 0x88) direction = 1;
        else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT) || input->specialKeyCode == 0x84) direction = 3;
        else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT) || input->specialKeyCode == 0x83) direction = 2;
        else return 0;
        int xPos = (int)x;
        int yPos = (int)y;
        int inc = (int)width / 4;
        int curinc = 0;
        for (int i = 0; i < 5; i++) {
            cur[i].x = xPos + (float)curinc;
            cur[i].y = yPos + height * 0.5f;
            curinc += inc;
        }
        ignoreZone = 10;
        getIntAttrib(xml, svoNavigationZoneAttribute, &ignoreZone);
        SVTag **tagList = page->m_pFrontDisplayBuffer->tagList;
        if (!tagList) __SVO_Assert_Handler(svoNavigationSource, 0x180);
        for (int n = 0; *tagList && n < 256; n++, tagList++) {
            SVTag *tag = *tagList;
            if (tag->vtable->IsSelected(tag) || !tag->vtable->IsSelectable(tag)) continue;
            float fbx = 0.0f;
            float fby = 0.0f;
            float fbw = 0.0f;
            float fbh = 0.0f;
            tag->vtable->GetDimensions(tag, &fbx, &fby, &fbw, &fbh);
            int targetInc = (int)fbw / 4;
            int targetPos = 0;
            for (int j = 0; j < 5; j++) {
                target[j].x = fbx + (float)targetPos;
                target[j].y = fby + fbh * 0.5f;
                targetPos += targetInc;
            }
            double dist;
            switch (direction) {
            case 0:
                if (target[2].y < cur[2].y) {
                    curTo.x = target[2].x;
                    curTo.y = target[2].y;
                    for (int k = 0; k < 5; k++) {
                        dist = getDistanceAutoNav((int)cur[2].x, (int)cur[2].y, (int)target[k].x, (int)target[k].y, direction, ignoreZone, 2);
                        if (lt_double(dist, shortest)) {
                            shortest = dist;
                            closest = tag;
                            curTo.x = target[k].x;
                            curTo.y = target[k].y;
                        }
                    }
                    curFrom.x = cur[2].x;
                    curFrom.y = cur[2].y;
                }
                break;
            case 1:
                if (cur[2].y < target[2].y) {
                    curTo.x = target[2].x;
                    curTo.y = target[2].y;
                    for (int k = 0; k < 5; k++) {
                        dist = getDistanceAutoNav((int)cur[2].x, (int)cur[2].y, (int)target[k].x, (int)target[k].y, direction, ignoreZone, 2);
                        if (lt_double(dist, shortest)) {
                            shortest = dist;
                            closest = tag;
                            curTo.x = target[k].x;
                            curTo.y = target[k].y;
                        }
                    }
                    curFrom.x = cur[2].x;
                    curFrom.y = cur[2].y;
                }
                break;
            case 2:
                if (target[4].x < cur[0].x) {
                    curTo.x = target[4].x;
                    curTo.y = target[4].y;
                    dist = getDistanceAutoNav((int)cur[0].x, (int)cur[0].y, (int)target[4].x, (int)target[4].y, 2, ignoreZone, 5);
                    if (lt_double(dist, shortest)) {
                        shortest = dist;
                        closest = tag;
                    }
                    curFrom.x = cur[0].x;
                    curFrom.y = cur[0].y;
                }
                break;
            case 3:
                if (cur[4].x < target[0].x) {
                    curTo.x = target[0].x;
                    curTo.y = target[0].y;
                    dist = getDistanceAutoNav((int)cur[4].x, (int)cur[4].y, (int)target[0].x, (int)target[0].y, 3, ignoreZone, 5);
                    if (lt_double(dist, shortest)) {
                        shortest = dist;
                        closest = tag;
                    }
                    curFrom.x = cur[4].x;
                    curFrom.y = cur[4].y;
                }
                break;
            default:
                __SVO_Assert_Handler(svoNavigationSource, 0x1E9);
                break;
            }
        }
        if (closest) {
            selected->vtable->SetSelectedState(selected, 0);
            closest->vtable->SetSelectedState(closest, 1);
            if (selected != closest) {
                CAudioContextBaseState *audio = GetAudioContext();
                ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 0, svoNavigationSoundClass);
            }
            draw->vtable->AnimateHighlight(draw, selected->vtable->GetTagID(selected), closest->vtable->GetTagID(closest));
            return 1;
        }
        if (!input->vtable->WrapSelections(input)) return 0;
        setWrapDimensions(direction, &x, &y, &width, &height, input);
    }
    return 0;
}

extern "C" SECTION(CNavInfo) void CNavInfo(CNavInfoState *nav)
{
    nav->right = 0;
    nav->up = 0;
    nav->down = 0;
    nav->left = 0;
}

extern "C" double pow(double, double);
double sqrt(double);
extern "C" SECTION(getDistanceAutoNav) float getDistanceAutoNav(int x, int y, int tx, int ty, int direction, int ignoreZone, int ignoreMult)
{
    if (direction >= 0) {
        if (direction < 2) {
            if (tx < x - ignoreZone) {
                double distance = (float)(x - tx);
                if (distance < 0) distance = 0 - distance;
                tx -= (int)distance * ignoreMult;
            } else if (tx > x + ignoreZone) {
                double distance = (float)(tx - x);
                if (distance < 0) distance = 0 - distance;
                tx += (int)distance * ignoreMult;
            }
            goto done;
        }
        if (direction < 4) {
            if (ty < y - ignoreZone) {
                double distance = (float)(y - ty);
                if (distance < 0) distance = 0 - distance;
                ty -= (int)distance * ignoreMult;
            } else if (ty > y + ignoreZone) {
                double distance = (float)(y - ty);
                if (distance < 0) distance = 0 - distance;
                ty += (int)distance * ignoreMult;
            }
            goto done;
        }
    }
    __SVO_Assert_Handler(svoNavigationSource, 0x5B);
done:
    return sqrt(pow(tx - x, 2.0) + pow(ty - y, 2.0));
}

extern "C" SECTION(lt_double) int lt_double(double a, double b)
{
    return (int)(a * 8.0) < (int)(b * 8.0);
}

extern "C" {
extern char svoNavigationSoundClass[];
int autoNavigate(SVTag *selected, CInputContextBaseState *input, CDrawContextBase *draw, iks *xml, CPage *page);
CNavInfoState *GetNavInfo(SVTag *tag);
int GetVisible(SVTag *tag);
CAudioContextBaseState *GetAudioContext(void);
CInputContextBaseState *GetInputContext(void);
}
extern "C" SECTION(Navigate) int Navigate(SVTag *selected, CInputContextBaseState *input, CDrawContextBase *draw, iks *xml, CPage *page)
{
    int changed = 0;
    int direction;
    if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP) || input->specialKeyCode == 0x81) direction = 0;
    else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN) || input->specialKeyCode == 0x82 || input->specialKeyCode == 0x88) direction = 1;
    else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT) || input->specialKeyCode == 0x84) direction = 3;
    else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT) || input->specialKeyCode == 0x83) direction = 2;
    else return 0;
    SVTag *target = 0;
    CNavInfoState *navigation = GetNavInfo(selected);
    char *name = 0;
    switch (direction) {
    case 0: name = navigation->up; break;
    case 1: name = navigation->down; break;
    case 2: name = navigation->left; break;
    case 3: name = navigation->right; break;
    default: __SVO_Assert_Handler(svoNavigationSource, 0xB0); break;
    }
    if (name) {
        target = getTagByName(name, page);
        if (target) {
            if (!target->vtable->IsSelectable(target) || !GetVisible(target)) GetNavInfo(target);
            else changed = 1;
        } else {
            __SVO_Assert_Handler(svoNavigationSource, 0xCE);
        }
    }
    if (changed) {
        selected->vtable->SetSelectedState(selected, 0);
        target->vtable->SetSelectedState(target, 1);
        CAudioContextBaseState *audio;
        if (target != selected) {
            audio = GetAudioContext();
            ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 0, svoNavigationSoundClass);
        } else {
            audio = GetAudioContext();
            ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 6, svoNavigationSoundClass);
        }
        draw->vtable->AnimateHighlight(draw, selected->vtable->GetTagID(selected), target->vtable->GetTagID(target));
    } else {
        changed = autoNavigate(selected, input, draw, xml, page);
    }
    if (changed) {
        CInputContextBaseState *keyboard = GetInputContext();
        keyboard->vtable->ResetKeyboardInput(keyboard);
    }
    return changed;
}

extern "C" SECTION(setWrapDimensions) void setWrapDimensions(int direction, float *x, float *y, float *width, float *height, CInputContextBaseState *input)
{
    float screenX;
    float screenY;
    input->vtable->GetScreenDimensions(input, &screenX, &screenY, width, height);
    if (direction == 0) *y = screenY + 1000.0f;
    else if (direction == 1) *y = -1000.0f;
    else if (direction == 2) *x = screenX + 1000.0f;
    else if (direction == 3) *x = -1000.0f;
    else __SVO_Assert_Handler(svoNavigationSource, 0x27B);
}
