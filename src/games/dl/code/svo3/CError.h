#ifndef CERROR_H
#define CERROR_H

extern "C" {
extern int svoErrorCode;
void SetErrorCode(int code);
int GetErrorCode(void);
}

#endif
