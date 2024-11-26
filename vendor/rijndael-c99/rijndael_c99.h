#ifndef RIJNDAEL_C99_H
#define RIJNDAEL_C99_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
	ECB = 0,
	CBC = 1,
	CFB = 2
} rijndael_mode;

#define DEFAULT_BLOCK_SIZE 16
#define MAX_BLOCK_SIZE 32
#define MAX_ROUNDS 14
#define MAX_KC 8
#define MAX_BC 8

typedef struct
{
	bool m_bKeyInit;
	int m_Ke[MAX_ROUNDS + 1][MAX_BC];
	int m_Kd[MAX_ROUNDS + 1][MAX_BC];
	int m_keylength;
	int	m_blockSize;
	int m_iROUNDS;
	char m_chain0[MAX_BLOCK_SIZE];
	char m_chain[MAX_BLOCK_SIZE];
	int tk[MAX_KC];
	int a[MAX_BC];
	int t[MAX_BC];
} rijndael_ctx;

extern void rijndael_init(rijndael_ctx *ctx);
extern int rijndael_make_key(rijndael_ctx *ctx, char const *key, char const *chain, int keylength, int blockSize);

extern int rijndael_encrypt_block(rijndael_ctx *ctx, char const *in, char *result);
extern int rijndael_decrypt_block(rijndael_ctx *ctx, char const *in, char *result);

extern int rijndael_encrypt(rijndael_ctx *ctx, char const *in, char *result, size_t n, rijndael_mode iMode);
extern int rijndael_decrypt(rijndael_ctx *ctx, char const *in, char *result, size_t n, rijndael_mode iMode);

extern const char *rijndael_get_zero_chain();

#endif