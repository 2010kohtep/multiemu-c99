#include "gen_revemu2013.h"

#include <string.h>
#include <time.h>

#include "../utils/rev_spoofer.h"
#include "../utils/rev_data.h"
#include "../utils/sse_hash.h"

int generate_revemu2013_by_number(void *dest, unsigned number)
{
	if (!dest)
		return 0;

	const char *rev_string = rev_spoof(number);
	if (!rev_string)
		return 0;

	return generate_revemu2013_by_string(dest, rev_string);
}

int generate_revemu2013_by_string(void *dest, const char *string)
{
	if (!dest || !string || !*string)
		return 0;

	int *ticket = (int *)dest;
	unsigned char *ticket_b = (unsigned char *)dest;
	unsigned hash = rev_hash(string);

	const int cur_time = (const int)time(0);

	ticket[0] = 'S';                               // +0
	ticket[1] = hash;                              // +4
	ticket[2] = 0x00726576;                        // +8, 'rev'
	ticket[3] = 0;                                 // +12
	ticket[4] = hash << 1;                         // +16, SteamId, Low part
	ticket[5] = 0x01100001;                        // +20, SteamId, High part
	ticket[6] = cur_time + 90123;                  // +24, 1 day, 1 hour, 2 minutes, and 3 seconds
	ticket_b[27] = ~(ticket_b[27] + ticket_b[24]); // +27
	ticket[7] = ~cur_time;                         // +28
	ticket[8] = hash * 2 >> 3;                     // +32
	ticket[9] = 0;                                 // +36

	if (!rev_write_aes_data(&ticket_b[40], string, rev_get_aes_rand_key()))
		return 0;

	if (!rev_write_aes_data(&ticket_b[72], rev_get_aes_rand_key(), rev_get_aes_rev_key()))
		return 0;

	if (!rev_write_sha_data(&ticket_b[104], string))
		return 0;

	return 194;
}