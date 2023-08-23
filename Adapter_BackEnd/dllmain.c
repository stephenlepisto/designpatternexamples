/// @file
/// @brief
/// Implementation of the DllMain() entry point for Windows.

#include "pch.h"

#ifdef _MSC_VER
/// @brief Entry point for the DLL (on Windows)
/// @param hModule Handle to this module (not used)
/// @param ul_reason_for_call (not used)
/// @param lpReserved (not used)
/// @return Always returns TRUE
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    (void)hModule; // reference it to avoid compiler warning
    (void)lpReserved; // reference it to avoid compiler warning

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#endif
