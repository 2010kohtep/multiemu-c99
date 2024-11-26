#include "gen_avsmp.h"

#include "../utils/sse_hash.h"

int generate_avsmp_by_number(void *dest, unsigned number, bool set_steam_x1x)
{
	if (!dest)
		return 0;

	int *ticket = (int *)dest;

	ticket[0] = 0x14;									 //  +0, header
	ticket[3] = (number << 1) | (set_steam_x1x ? 1 : 0); // +12, SteamId, Low part
	ticket[4] = 0x01100001;								 // +16, SteamId, High part

	return 28;
}

int generate_avsmp_by_string(void *dest, const char *string, bool set_steam_x1x)
{
	if (!dest || !string || !*string)
		return 0;

	return generate_avsmp_by_number(dest, sse_hash_string(string), set_steam_x1x);
}