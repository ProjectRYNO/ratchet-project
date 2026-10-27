#include "common.h"
#include "libscf.h"

/* Recovered directly from the retail boot instructions; no vendor source. */
#define SCF_SECTION(name) __attribute__((section(".scf_" #name)))

/* Functions not yet recovered, and original padding words, stay in their own slots. */
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
	__asm__(".section .scf_" #NAME ",\"ax\",@progbits\n" \
		".set noat\n.set noreorder\n" \
		".include \"" FOLDER "/" #NAME ".s\"\n" \
		".set reorder\n.set at\n.text\n")
#endif

extern char sdkScfRomName[];
extern const char sdkScfRomVerPath[];
extern short sdkScfT10kTimeZone;
extern unsigned char sdkScfT10kAspect;
extern unsigned char sdkScfT10kLanguage;
extern unsigned char sdkScfT10kSummerTime;
extern const scfMonthDays_t sdkScfMonthDays;
extern int sceOpen(const char *, int);
extern int sceRead(int, void *, int);
extern int sceClose(int);
extern void GetOsdConfigParam(scfOsdConfig_t *);
extern void GetOsdConfigParam2(void *, int, int);
char *GetRomName(void);
int IsT10K(void);
unsigned char frombcd(unsigned char value);
unsigned char tobcd(unsigned char value);
void adddate(scfClock_t *clock);
void subdate(scfClock_t *clock);

char *SCF_SECTION(GetRomName) GetRomName(void)
{
	if (!sdkScfRomName[0]) {
		int fd = sceOpen(sdkScfRomVerPath, 1);
		if (fd >= 0) {
			sceRead(fd, sdkScfRomName, 0xe);
			sceClose(fd);
		}
	}
	return sdkScfRomName;
}

int SCF_SECTION(IsT10K) IsT10K(void)
{
	if (!sdkScfRomName[0]) GetRomName();
	return sdkScfRomName[4] == 'T';
}

int SCF_SECTION(sceScfGetLanguage) sceScfGetLanguage(void)
{
	scfOsdConfig_t config;
	int language;
	GetOsdConfigParam(&config);
	if (IsT10K()) {
		language = sdkScfT10kLanguage;
	} else {
		GetOsdConfigParam(&config);
		if (!config.version) language = config.japLanguage;
		else language = config.language;
	}
	return language;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/scf/libscf", func_00155620);

int SCF_SECTION(sceScfGetAspect) sceScfGetAspect(void)
{
	scfOsdConfig_t config;
	if (IsT10K()) return sdkScfT10kAspect;
	GetOsdConfigParam(&config);
	return config.screenType;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/scf/libscf", func_00155668);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/scf/libscf", sceScfGetTimeZone);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/scf/libscf", func_001556C0);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/scf/libscf", sceScfGetSummerTime);

unsigned char SCF_SECTION(tobcd) tobcd(unsigned char value)
{
	return value + (value / 10) * 6;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/scf/libscf", frombcd);

void SCF_SECTION(convertfrombcd) convertfrombcd(scfClock_t *clock)
{
	clock->year = frombcd(clock->year);
	clock->month = frombcd(clock->month);
	clock->day = frombcd(clock->day);
	clock->hour = frombcd(clock->hour);
	clock->minute = frombcd(clock->minute);
	clock->second = frombcd(clock->second);
}

void SCF_SECTION(converttobcd) converttobcd(scfClock_t *clock)
{
	clock->year = tobcd(clock->year);
	clock->month = tobcd(clock->month);
	clock->day = tobcd(clock->day);
	clock->hour = tobcd(clock->hour);
	clock->minute = tobcd(clock->minute);
	clock->second = tobcd(clock->second);
}

void SCF_SECTION(adddate) adddate(scfClock_t *clock)
{
	scfMonthDays_t month = sdkScfMonthDays;
	clock->day++;
	if (clock->year % 4 == 0) month.days[1] = 29;
	if (month.days[clock->month - 1] < clock->day) {
		clock->day = 1;
		clock->month++;
		if (clock->month == 13) {
			if (clock->year == 99) clock->year = 0;
			else clock->year++;
			clock->month = 1;
		}
	}
}

void SCF_SECTION(subdate) subdate(scfClock_t *clock)
{
	scfMonthDays_t month = sdkScfMonthDays;
	clock->day--;
	if (clock->year % 4 == 0) month.days[1] = 29;
	if (!clock->day) {
		clock->month--;
		if (!clock->month) {
			if (clock->year) clock->year--;
			else clock->year = 99;
			clock->month = 12;
		}
		clock->day = month.days[clock->month - 1];
	}
}

void SCF_SECTION(addhour) addhour(scfClock_t *clock)
{
	if (++clock->hour == 24) {
		clock->hour = 0;
		adddate(clock);
	}
}

void SCF_SECTION(subhour) subhour(scfClock_t *clock)
{
	if (!clock->hour) {
		clock->hour = 23;
		subdate(clock);
	} else {
		clock->hour--;
	}
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/scf/libscf", AdjustTime);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/sdk/scf/libscf", sceScfGetLocalTimefromRTC);
