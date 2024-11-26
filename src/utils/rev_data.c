#include "rev_data.h"

#include <stdlib.h>
#include <string.h>

#include "../../vendor/rijndael-c99/rijndael_c99.h"
#include "../../vendor/crypto-algorithms/sha256.h"

#define BLOCK_SIZE 32
#define KEY_SIZE 32

static const char aes_key_rand[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
static const char aes_key_rev[] = "_YOU_SERIOUSLY_NEED_TO_GET_LAID_";

const char *rev_get_aes_rand_key()
{
	return aes_key_rand;
}

const char *rev_get_aes_rev_key()
{
	return aes_key_rev;
}

bool rev_write_aes_data(void *dest, const char *src, const char *key)
{
	size_t len = strlen(src);
	if (len > BLOCK_SIZE)
		return false;

	char src_pad[BLOCK_SIZE];
	memset(src_pad, 0, sizeof(src_pad));
	memcpy(src_pad, src, len);
	src = src_pad;

	rijndael_ctx ctx;
	rijndael_init(&ctx);

	if (rijndael_make_key(&ctx, key, rijndael_get_zero_chain(), KEY_SIZE, BLOCK_SIZE) < 0)
		return false;

	if (rijndael_encrypt_block(&ctx, src_pad, dest) < 0)
		return false;

	return true;
}

bool rev_write_sha_data(void *dest, const char *src)
{
	size_t len = strlen(src);

	if (len > 32)
		return false;

	char src_pad[32];
	memset(src_pad, 0, sizeof(src_pad));
	memcpy(src_pad, src, len);

	SHA256_CTX ctx;
	sha256_init(&ctx);
	sha256_update(&ctx, src_pad, SHA256_BLOCK_SIZE);
	sha256_final(&ctx, dest);

	return true;
}