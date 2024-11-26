#ifndef GEN_AVSMP_H
#define GEN_AVSMP_H

#include <stdbool.h> // bool

extern int generate_avsmp_by_number(void *dest, unsigned number, bool set_steam_x1x);
extern int generate_avsmp_by_string(void *dest, const char *payload, bool set_steam_x1x);

#endif