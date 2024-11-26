#include "gen_setti.h"

int generate_setti(void *dest)
{
	if (!dest)
		return 0;

	int *pTicket = (int *)dest;

	pTicket[0] = 0xD4CA7F7B;
	pTicket[1] = 0xC7DB6023;
	pTicket[2] = 0x6D6A2E1F;
	pTicket[5] = 0xB4C43105;

	return 768;
}