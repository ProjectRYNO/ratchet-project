#include "common.h"
#include "game_section.h"

/* Recovered from the retail boot instructions, using names from the prototype's debug data. */
struct MapNameDataCell {
	/* 0x00 */ int city_name;
	/* 0x04 */ int planet_name;
};

extern MapNameDataCell MapNameDataMap[] __asm__("D_21F530");
extern const char sdkPlanetNameFormat[] __asm__("D_21F540");
char *msg_string(int) __asm__("msg_string");
extern "C" int sprintf(char *, const char *, ...);
bool InBootUpTopPage() __asm__("InBootUpTopPage");
char *GetFormattedPlanetName(char *yourBuffer, int level) __asm__("GetFormattedPlanetName");

inline bool isPlanetNamePrepended(int level)
{
	switch (level) {
	case 2:
	case 5:
	case 10:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1a:
		return false;
	default:
		return true;
	}
}

inline int getPlanetNameId(int level)
{
	int id;
	if (level >= 0) id = MapNameDataMap[level % 0x50].planet_name;
	else id = 0;
	return id;
}

GAME_SECTION(InBootUpTopPage) bool InBootUpTopPage()
{
	return false;
}

GAME_SECTION(GetFormattedPlanetName) char *GetFormattedPlanetName(char *yourBuffer, int level)
{
	bool prependPlanet = isPlanetNamePrepended(level);
	if (!prependPlanet) {
		sprintf(yourBuffer, sdkPlanetNameFormat, msg_string(getPlanetNameId(level)));
	}
	return yourBuffer;
}
