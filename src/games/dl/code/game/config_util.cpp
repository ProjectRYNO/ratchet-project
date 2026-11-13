#include "common.h"
#include "game_section.h"

extern "C" double atof(const char *);
unsigned char *ConfigUtil_ReadNumber(unsigned char *word, float &number) __asm__("ConfigUtil_ReadNumber");
inline bool isDigit(int c)
{
	return (unsigned int)(c - 0x30) < 10;
}


typedef struct configUtilCodexElement {
	/* 0x00 */ char m_word[0x38];
	/* 0x38 */ unsigned int m_length;
	/* 0x3c */ int m_word_val;
} configUtilCodexElement_t;
typedef struct configUtilCodex {
	/* 0x00 */ configUtilCodexElement_t *m_elems;
	/* 0x04 */ unsigned int m_num_elems;
} configUtilCodex_t;
extern "C" int strncmp(const char *, const char *, unsigned int);
unsigned char *ConfigUtil_ReadLine(unsigned char *input, unsigned char *buff, unsigned int buff_size) __asm__("ConfigUtil_ReadLine");
unsigned char *ConfigUtil_ReadWord(unsigned char *word, configUtilCodex_t *codex, int &key_word) __asm__("ConfigUtil_ReadWord");
inline bool isAlpha(int c)
{
	return (unsigned int)(c - 0x41) < 26 || (unsigned int)(c - 0x61) < 26;
}


INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/config_util", ConfigUtil_ParseLine);

GAME_SECTION(ConfigUtil_ReadLine) unsigned char *ConfigUtil_ReadLine(unsigned char *input, unsigned char *buff, unsigned int buff_size)
{
	int comment = 0;
	int quote = 0;
	unsigned int cnt;
	for (cnt = 0; cnt < buff_size - 1; cnt++) {
		if (*input == 0x22 && input[-1] != 0x5c) quote = !quote;
		if (*input == 0xa && !quote) break;
		if (*input == 0) break;
		if (*input == 0x3b) comment = !comment;
		if (*input != 0xd && !comment) *buff++ = *input;
		input++;
	}
	*buff = 0;
	unsigned char *ret = input + 1;
	if (!*input) ret = input;
	return ret;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/config_util", ConfigUtil_ReadWord);

GAME_SECTION(ConfigUtil_ReadNumber) unsigned char *ConfigUtil_ReadNumber(unsigned char *word, float &number)
{
	unsigned int c;
	number = atof((char *)word);
	while (isDigit(c = *word) || (unsigned char)c == 0x2e || (unsigned char)c == 0x2d) word++;
	return word;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/config_util", func_004FDCF0);
