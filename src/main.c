#include <Windows.h>

#include "impl/emu_impl.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		init_emulator();
		return TRUE;
	}

	if (fdwReason == DLL_PROCESS_DETACH)
	{
		shutdown_emulator();
		return TRUE;
	}

	return TRUE;
}