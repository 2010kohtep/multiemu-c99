#include "sse_hash.h"

#include <string.h>

static int rotl(int value, int shift)
{
    const int bits = 32;
    shift %= bits;
    return (value << shift) | (value >> (bits - shift));
}

static int sse_hash_seed(const void *data, int size, int seed)
{
	if (!data)
		return 0;

	int *p = (int *)data;

	for (int i = 0; i < 8; i++)
	{
		int h1 = rotl(0xCC9E2D51 * p[i], 15);
		int h2 = rotl(0x1B873593 * h1 ^ seed, 13);
		seed = 5 * (h2 - 0x052250EC);
	}

	int hash = seed ^ size;
	hash ^= hash >> 16;
	hash *= 0x85EBCA6B;
	hash ^= hash >> 13;
	hash *= 0xC2B2AE35;
	hash ^= hash >> 16;

	return hash;
}

int sse_hash_buffer(void *data, int size)
{
	return sse_hash_seed(data, size, 47);
}

int sse_hash_string(const char *string)
{
	if (!string || !*string)
		return 0;

	return sse_hash_seed(string, strlen(string), 47);
}