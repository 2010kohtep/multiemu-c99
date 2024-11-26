#include "emu_impl.h"

#include <Windows.h>

#include "../features/gen_revemu.h"
#include "../features/gen_avsmp.h"
#include "../features/gen_oldrevemu.h"
#include "../features/gen_setti.h"
#include "../features/gen_steamemu.h"
#include "../features/gen_revemu2013.h"
#include "../features/gen_sc2009.h"

typedef void *ISteamUser;

typedef int(__fastcall *initialize_game_connection_t)(ISteamUser *self, void *, void *pData, int cbMaxData, long long steamID, int unIPServer, short usPortServer, int bSecure);
typedef ISteamUser *(__fastcall *steam_user_t)();

static initialize_game_connection_t pfn_initialize_game_connection = 0;

static const char *generate_hwid()
{
	return "Samsung-860EVO-SN123456789";
}

static int __fastcall hk_initialize_game_connection(ISteamUser * self, void *dummy, void *pData, int cbMaxData, long long steamID, int unIPServer, short usPortServer, int bSecure)
{
	return generate_revemu2013_by_string(pData, generate_hwid());
}

static HMODULE find_steam_api_dll()
{
	return GetModuleHandleA("steam_api.dll");
}

static initialize_game_connection_t hook_cert_generator(initialize_game_connection_t hook)
{
	if (!hook)
		return 0;

	HMODULE hSteamAPI = find_steam_api_dll();
	if (!hSteamAPI)
		return 0;

	steam_user_t pfnSteamUser = (steam_user_t)GetProcAddress(hSteamAPI, "SteamUser");
	if (!pfnSteamUser)
		return 0;

	ISteamUser *pSteamUser = pfnSteamUser();
	if (!pSteamUser)
		return 0;

	/* Get pointer to InitiateGameConnection method address in virtual table of ISteamUser interface. */
	void **pfn = &((void **)(*(void **)pSteamUser))[3];

	/* Save original InitiateGameConnection method code address. */
	initialize_game_connection_t original = (initialize_game_connection_t)*pfn;

	/* Write own InitiateGameConnection function address to virtual table. */
	DWORD oldProtect;
	VirtualProtect(pfn, sizeof(void *), PAGE_READWRITE, &oldProtect);
	*pfn = hook;
	VirtualProtect(pfn, sizeof(void *), oldProtect, &oldProtect);

	return original;
}

bool init_emulator()
{
	pfn_initialize_game_connection = hook_cert_generator(hk_initialize_game_connection);
	return (pfn_initialize_game_connection != 0);
}

bool shutdown_emulator()
{
	return hook_cert_generator(pfn_initialize_game_connection) != 0;
}