#ifndef SDK_SCF_LIBSCF_H
#define SDK_SCF_LIBSCF_H

/* OSD configuration word (GetOsdConfigParam); timezoneOffset is signed minutes. */
typedef struct scfOsdConfig {
	/* 0x00 */ unsigned int spdifMode : 1;
	unsigned int screenType : 2;
	unsigned int videoOutput : 1;
	unsigned int japLanguage : 1;
	unsigned int ps1drvConfig : 8;
	unsigned int version : 3;
	unsigned int language : 5;
	int timezoneOffset : 11;
} scfOsdConfig_t;

/* sceCdCLOCK: BCD real-time clock fields. */
typedef struct scfClock {
	/* 0x00 */ unsigned char stat;
	/* 0x01 */ unsigned char second;
	/* 0x02 */ unsigned char minute;
	/* 0x03 */ unsigned char hour;
	/* 0x04 */ unsigned char pad;
	/* 0x05 */ unsigned char day;
	/* 0x06 */ unsigned char month;
	/* 0x07 */ unsigned char year;
} scfClock_t;

/* Days per month, copied to the stack by adddate/subdate. */
typedef struct scfMonthDays {
	/* 0x00 */ char days[12];
} scfMonthDays_t;

#endif
