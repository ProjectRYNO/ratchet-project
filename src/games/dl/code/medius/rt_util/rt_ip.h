#ifndef RT_IP_H
#define RT_IP_H

#ifdef __cplusplus
extern "C" {
#endif

// Dotted-quad conversion; the first octet is the address's low byte.
unsigned int rt_ip_string2ip(const char *string);
void rt_ip_ip2string(char *string, unsigned int ip);

#ifdef __cplusplus
}
#endif

#endif
