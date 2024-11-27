#include "gen_revemu.h"

#include <string.h>

#include "../utils/rev_spoofer.h"
#include "../utils/sse_hash.h"

int generate_revemu_by_number(void *dest, unsigned number)
{
	if (!dest)
		return 0;

	const char *rev_string = rev_spoof(number);
	if (!rev_string)
		return 0;

	return generate_revemu_by_string(dest, rev_string);
}

int generate_revemu_by_string(void *dest, const char *string)
{
	if (!dest || !string || !*string)
		return 0;

	int *ticket = (int *)dest;
	unsigned hash = rev_hash(string);

	ticket[0] = 'J';        //  +0, header
	ticket[1] = hash;       //  +4, hash of string at +24 offset
	ticket[2] = 0x00726576; //  +8, 'rev'
	ticket[3] = 0;          // +12, unknown number, must always be 0
						    
	ticket[4] = hash << 1;  // +16, SteamId, Low part
	ticket[5] = 0x01100001; // +20, SteamId, High part

	strcpy((char *)&ticket[6], string); // +24, string for hash

	return 152;
}