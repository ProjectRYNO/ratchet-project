#ifndef UTF8_UTIL_H
#define UTF8_UTIL_H

struct CDrawContextBase;
enum eUTF8CharacterType {
    kTypeStartSingleByte = 0,
    kTypeStartTwoBytes = 1,
    kTypeStartThreeBytes = 2,
    kTypeStartFourBytes = 3,
    kTypeContinuationByte = 4,
    kTypeInvalid = 5
};

extern "C" {
eUTF8CharacterType UTF8_GetCharacterType(char byte);
int UTF8_GetPrevCharIndexFromString(char *text, int index);
int UTF8_GetNextCharIndexFromString(char *text, int index);
int UTF8_RemoveCharFromStringBACKSPACE(char *text, int index);
int UTF8_RemoveCharFromStringDELETE(char *text, int index);
int UTF8_AddCharToString(char *text, unsigned int capacity, char *input, int inputSize, int index);
int UTF8_TrimStringToFitLength(char *text, float length, int fontSize, CDrawContextBase *draw);
int CheckContinuationCharacters(char *text, unsigned int size, unsigned int count);
int UTF8_CountCharacters(char *text, unsigned int size);
}
#endif
