#ifndef REV_SPOOFER_H
#define REV_SPOOFER_H

#include <stdbool.h> // bool
#include <stdlib.h> // size_t, rand, _countof

extern unsigned rev_hash(const char *str);

extern bool rev_spoof_ex(char *result, size_t size, unsigned value);
extern const char *rev_spoof(unsigned value);

#endif