#ifndef REV_DATA_H
#define REV_DATA_H

#include <stdbool.h>

extern const char *rev_get_aes_rand_key();
extern const char *rev_get_aes_rev_key();

extern bool rev_write_aes_data(void *dest, const char *src, const char *key);
extern bool rev_write_sha_data(void *dest, const char *src);

#endif