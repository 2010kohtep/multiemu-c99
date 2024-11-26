#include "rev_spoofer.h"

#include <string.h> // strlen
#include <assert.h>

static char rev_dictionary[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

typedef char rev_string_t[32 + sizeof(char)];
static rev_string_t rev_strings[8];
static size_t rev_strings_counter = 0;

static void create_random_string(char *dest, size_t length)
{
	for (unsigned i = 0; i < length; ++i)
		dest[i] = rev_dictionary[rand() % (_countof(rev_dictionary) - 1)];
}

static bool rev_scan_last_3(char *input, size_t size, unsigned expecting, unsigned prev_result)
{
	unsigned h1, h2, h3, hh;

	for (unsigned i1 = 0; i1 < _countof(rev_dictionary); i1++)
	{
		h1 = prev_result ^ ((prev_result >> 2) + (prev_result << 5) + rev_dictionary[i1]);
		hh = h1 ^ ((h1 >> 2) + (h1 << 5));
		hh = hh ^ ((hh >> 2) + (hh << 5));

		if ((hh ^ expecting) >> (8 + 5 + 3))
			continue;

		for (unsigned i2 = 0; i2 < _countof(rev_dictionary); i2++)
		{
			h2 = h1 ^ ((h1 >> 2) + (h1 << 5) + rev_dictionary[i2]);
			hh = h2 ^ ((h2 >> 2) + (h2 << 5));

			if ((hh ^ expecting) >> (8 + 3))
				continue;

			for (unsigned i3 = 0; i3 < _countof(rev_dictionary); i3++)
			{
				h3 = h2 ^ ((h2 >> 2) + (h2 << 5) + rev_dictionary[i3]);

				if (h3 == expecting)
				{
					input[size - 3] = rev_dictionary[i1];
					input[size - 2] = rev_dictionary[i2];
					input[size - 1] = rev_dictionary[i3];

					return true;
				}
			}
		}
	}

	return false;
}

static bool rev_scan_next(char *input, size_t size, size_t index, unsigned expecting, unsigned prev_result)
{
	bool res;

	for (unsigned i = 0; i < _countof(rev_dictionary); i++)
	{
		auto h = prev_result ^ ((prev_result >> 2) + (prev_result << 5) + rev_dictionary[i]);

		if (index + 1 < size - 3)
		{
			res = rev_scan_next(input, size, index + 1, expecting, h);
		}
		else
		{
			res = rev_scan_last_3(input, size, expecting, h);
		}

		if (res)
		{
			input[index] = rev_dictionary[i];
			return true;
		}
	}
	
	return false;
}

unsigned rev_hash(const char *str)
{
	int i = 0;
	unsigned nHash = 0x4E67C6A7;
	int c = str[i++];

	while (c)
	{
		nHash = nHash ^ ((nHash >> 2) + (nHash << 5) + c);
		c = str[i++];
	}

	return nHash;
}

bool rev_spoof_ex(char *result, size_t length, unsigned value)
{
	if (!result || length < 8)
		return false;

	create_random_string(result, length);

	return rev_scan_next(result, length, length - 8, value, rev_hash(result));
}

const char *rev_spoof(unsigned value)
{
	char *result = rev_strings[(rev_strings_counter + 1) % _countof(rev_strings)];
	if (!rev_spoof_ex(result, sizeof(rev_string_t) - 1, value))
		return NULL;

	rev_strings_counter++;
	return result;
}