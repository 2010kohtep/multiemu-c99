#include "gen_oldrevemu.h"

#include "../utils/sse_hash.h"

int generate_oldrevemu_by_number(void *dest, unsigned number)
{
	if (!dest)
		return 0;

	int *pTicket = (int *)dest;
	unsigned char *pbTicket = (unsigned char *)dest;

	pTicket[0] = 0xFFFF;
	pTicket[1] = (number ^ 0xC9710266) << 1;
	*(short *)&pbTicket[8] = 0; // unknown; equals to 0 in original emulator

	return 10;
}

int generate_oldrevemu_by_string(void *dest, const char *string)
{
	if (!dest || !string || !*string)
		return 0;

	return generate_oldrevemu_by_number(dest, sse_hash_string(string));
}