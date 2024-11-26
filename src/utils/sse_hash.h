#ifndef GEN_SSE_HASH_H
#define GEN_SSE_HASH_H

/*
	Hash function used in the SmartSteamEmu (SSE).
*/

extern int sse_hash_buffer(void *data, int size);
extern int sse_hash_string(const char *string);

#endif