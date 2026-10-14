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
    eUTF8CharacterType type;
    int upper = byte & 0xF0;
    if (upper < 0x80) {
        type = kTypeStartSingleByte;
    } else if ((byte & 0xC0) == 0x80) {
        type = kTypeContinuationByte;
    } else {
        switch (upper) {
        case 0xF0:
            type = kTypeStartFourBytes;
            break;
        case 0xC0:
            type = kTypeStartTwoBytes;
            break;
        // Retail classifies 0xD0..0xDF as three-byte starts, too.
        case 0xD0:
        case 0xE0:
            type = kTypeStartThreeBytes;
            break;
        default:
            __SVO_Assert_Handler(svoUTF8Source, 0x38);
            type = kTypeInvalid;
            break;
        }
    }
    return type;
}

int UTF8_SECTION(UTF8_GetPrevCharIndexFromString) UTF8_GetPrevCharIndexFromString(char *text, int index)
{
    if (index > 0) {
        index--;
        while (index > 0 && UTF8_GetCharacterType(text[index]) == kTypeContinuationByte) index--;
    }
    return index;
}

int UTF8_SECTION(UTF8_GetNextCharIndexFromString) UTF8_GetNextCharIndexFromString(char *text, int index)
{
    int length = strlen(text);
    if (index >= length) return length;
    switch (UTF8_GetCharacterType(text[index])) {
    case kTypeStartTwoBytes:
        index += 2;
        break;
    case kTypeStartThreeBytes:
        index += 3;
        break;
    case kTypeStartFourBytes:
        index += 4;
        break;
    case kTypeContinuationByte:
    case kTypeInvalid:
        __SVO_Assert_Handler(svoUTF8Source, 0x75);
    case kTypeStartSingleByte:
        ++index;
        break;
    }
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
    if (length < index) __SVO_Assert_Handler(svoUTF8Source, 0xA3);
    if (length + inputSize >= (int)capacity) __SVO_Assert_Handler(svoUTF8Source, 0xA4);
    if (index < length) {
        char *insert = text + index;
        int end = index + inputSize;
        int tail = length - index;
        memmove(text + end, insert, tail);
        memcpy(insert, input, inputSize);
        text[end + tail] = 0;
    } else {
        strcat(text, input);
    }
    return index + inputSize;
}

int UTF8_SECTION(UTF8_TrimStringToFitLength) UTF8_TrimStringToFitLength(
    char *text, float length, int fontSize, CDrawContextBase *draw)
{
    int originalLength = strlen(text);
    int currentLength = originalLength;
    int removed = 0;
    // The width callback always receives the original byte count in retail.
    float width = draw->vtable->GetStringWidth(draw, fontSize, text, originalLength);
    while (length < width) {
        currentLength = UTF8_RemoveCharFromStringBACKSPACE(text, currentLength);
        width = draw->vtable->GetStringWidth(draw, fontSize, text, originalLength);
        ++removed;
    }
    return originalLength - removed;
}

int UTF8_SECTION(CheckContinuationCharacters) CheckContinuationCharacters(
    char *text, unsigned int size, unsigned int count)
{
    // Retail reports success when the remaining buffer is too short.
    int valid = 1;
    if (size >= count) {
        unsigned int i = 0;
        while (i < count && valid) {
            if (UTF8_GetCharacterType(text[i++]) != kTypeContinuationByte) valid = 0;
        }
    }
    return valid;
}

int UTF8_SECTION(UTF8_CountCharacters) UTF8_CountCharacters(char *text, unsigned int size)
{
    unsigned int count = 0;
    while (size) {
        unsigned int continuations;
        switch (UTF8_GetCharacterType(*text)) {
        case kTypeStartFourBytes:
            continuations = 3;
            break;
        case kTypeStartThreeBytes:
            continuations = 2;
            break;
        case kTypeStartTwoBytes:
            continuations = 1;
            break;
        case kTypeInvalid:
        default:
            __SVO_Assert_Handler(svoUTF8Source, 0x103);
        case kTypeStartSingleByte:
        case kTypeContinuationByte:
            continuations = 0;
            break;
        }
        ++text;
        --size;
        if (CheckContinuationCharacters(text, size, continuations)) {
            text += continuations;
            size -= continuations;
            ++count;
        }
    }
    return count;
}
