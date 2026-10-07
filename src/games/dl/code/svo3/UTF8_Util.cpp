#include "UTF8_Util.h"
#include "CDrawContextBase.h"
#include <string.h>

extern "C" {
extern char svoUTF8Source[];
void __SVO_Assert_Handler(const char *file, int line);
}
#define UTF8_SECTION(name) __attribute__((section(".svo_utf8_" #name)))

eUTF8CharacterType UTF8_SECTION(UTF8_GetCharacterType) UTF8_GetCharacterType(char byte)
{
    int upper = byte & 0xF0;
    if (upper < 0x80) return kTypeStartSingleByte;
    if ((byte & 0xC0) == 0x80) return kTypeContinuationByte;
    if (upper == 0xC0) return kTypeStartTwoBytes;
    // Retail classifies 0xD0..0xDF as three-byte starts, too.
    if (upper == 0xD0 || upper == 0xE0) return kTypeStartThreeBytes;
    if (upper == 0xF0) return kTypeStartFourBytes;
    __SVO_Assert_Handler(svoUTF8Source, 0x38);
    return kTypeInvalid;
}

int UTF8_SECTION(UTF8_GetPrevCharIndexFromString) UTF8_GetPrevCharIndexFromString(char *text, int index)
{
    if (index > 0) {
        do {
            --index;
            if (index <= 0) break;
        } while (UTF8_GetCharacterType(text[index]) == kTypeContinuationByte);
    }
    return index;
}

int UTF8_SECTION(UTF8_GetNextCharIndexFromString) UTF8_GetNextCharIndexFromString(char *text, int index)
{
    int length = strlen(text);
    if (index >= length) return length;
    int type = UTF8_GetCharacterType(text[index]);
    if (type == kTypeStartTwoBytes) return index + 2;
    if (type == kTypeStartThreeBytes) return index + 3;
    if (type == kTypeStartFourBytes) return index + 4;
    if (type == kTypeContinuationByte || type == kTypeInvalid)
        __SVO_Assert_Handler(svoUTF8Source, 0x75);
    if ((unsigned int)type < 6) ++index;
    return index;
}

int UTF8_SECTION(UTF8_RemoveCharFromStringBACKSPACE) UTF8_RemoveCharFromStringBACKSPACE(char *text, int index)
{
    int tail = (unsigned int)strlen(text) - index;
    int previous = UTF8_GetPrevCharIndexFromString(text, index);
    if (tail > 0) memmove(text + previous, text + index, tail);
    text[previous + tail] = 0;
    return previous;
}

int UTF8_SECTION(UTF8_RemoveCharFromStringDELETE) UTF8_RemoveCharFromStringDELETE(char *text, int index)
{
    int length = strlen(text);
    int next = UTF8_GetNextCharIndexFromString(text, index);
    memmove(text + index, text + next, length - next);
    text[index + length - next] = 0;
    return index;
}

int UTF8_SECTION(UTF8_AddCharToString) UTF8_AddCharToString(
    char *text, unsigned int capacity, char *input, int inputSize, int index)
{
    int length = strlen(text);
    int tail = (unsigned int)length - index;
    if (length < index) __SVO_Assert_Handler(svoUTF8Source, 0xA3);
    if ((int)capacity <= (int)((unsigned int)length + inputSize))
        __SVO_Assert_Handler(svoUTF8Source, 0xA4);
    if (index < length) {
        memmove(text + index + inputSize, text + index, tail);
        memcpy(text + index, input, inputSize);
        text[index + inputSize + tail] = 0;
    } else {
        strcat(text, input);
    }
    return (unsigned int)index + inputSize;
}

int UTF8_SECTION(UTF8_TrimStringToFitLength) UTF8_TrimStringToFitLength(
    char *text, float length, int fontSize, CDrawContextBase *draw)
{
    int originalLength = strlen(text);
    int currentLength = originalLength;
    int removed = 0;
    // The width callback always receives the original byte count in retail.
    while (length < draw->vtable->GetStringWidth(draw, fontSize, text, originalLength)) {
        currentLength = UTF8_RemoveCharFromStringBACKSPACE(text, currentLength);
        ++removed;
    }
    return originalLength - removed;
}

int UTF8_SECTION(CheckContinuationCharacters) CheckContinuationCharacters(
    char *text, unsigned int size, unsigned int count)
{
    // Preserve retail's success result when the remaining buffer is too short.
    if (count > size) return 1;
    int valid = 1;
    while (count && valid) {
        valid = UTF8_GetCharacterType(*text++) == kTypeContinuationByte;
        --count;
    }
    return valid;
}

int UTF8_SECTION(UTF8_CountCharacters) UTF8_CountCharacters(char *text, unsigned int size)
{
    unsigned int count = 0;
    while (size) {
        unsigned int continuations = 0;
        int type = UTF8_GetCharacterType(*text);
        if (type >= kTypeStartTwoBytes && type <= kTypeStartFourBytes)
            continuations = type;
        else if (type != kTypeStartSingleByte && type != kTypeContinuationByte)
            __SVO_Assert_Handler(svoUTF8Source, 0x103);
        ++text;
        --size;
        if (CheckContinuationCharacters(text, size, continuations)) {
            size -= continuations;
            text += continuations;
            ++count;
        }
    }
    return count;
}
