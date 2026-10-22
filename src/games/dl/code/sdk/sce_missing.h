#ifndef SCE_MISSING_H
#define SCE_MISSING_H

// Retail Sony SDK calls that PS2SDK does not declare (or declares under another name).
// Everything PS2SDK does provide comes from its headers (kernel.h, libcdvd-common.h, ...),
// which the Makefile puts on the include path with -D_EE. Signatures here are taken from
// the retail call sites; add an entry only when a PS2SDK equivalent is missing, and
// record its first user.

#include <libcdvd-common.h>

#ifdef __cplusplus
extern "C" {
#endif

// IOP device control (Sony libkernl). PS2SDK only has fileXioDevctl, a different RPC.
// First user: rt_time_platform_update_date_time ("cdrom0:", 0x430C reads the RTC).
int sceDevctl(const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);

// Console-configuration RTC conversion (Sony libscf, proposed sdk/scf/). PS2SDK's nearest
// is configConvertToLocalTime in osd_config.h, which is not the same symbol.
// First user: rt_time_platform_update_date_time.
int sceScfGetLocalTimefromRTC(sceCdCLOCK *rtc);

#ifdef __cplusplus
}
#endif

#endif
