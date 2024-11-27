#include "gen_steamemu.h"

#include "../utils/sse_hash.h"

int generate_steamemu_by_number(void *dest, unsigned number)
{
	if (!dest)
		return 0;

	int *pTicket = (int *)dest;

	// +80, dproto/reunion wants this value to be -1, but if this value
	//      does not match -1, then instead of SteamID in [21] cell
	//      client IP address that xored with 0x25730981 number should 
	//      be used. But dproto/reunion will just skip ticket validation
	//      in that case.
	pTicket[20] = -1;

	// +84, SteamId, low part. Actually, this is just system volume serial
	//      number, which comes from GetVolumeInformationA() function. If
	//      function failed (returned 0), then instead of volume serial number
	//      777 number will be written to the ticket.
	pTicket[21] = number;	
	
	return 768;
}

int generate_steamemu_by_string(void *dest, const char *string)
{
	if (!dest || !string || !*string)
		return 0;

	return generate_steamemu_by_number(dest, sse_hash_string(string));
}