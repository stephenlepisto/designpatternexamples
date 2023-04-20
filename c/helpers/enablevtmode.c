/// @file
/// @brief
/// Implementation of the enableVTMode() function
/// for configuring standard input to support the virtual terminal mode (on Windows).

#ifdef _MSC_VER
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include "enablevtmode.h"

#ifdef _MSC_VER
DWORD INVALID_MODE = 0xffffffff;        ///< Indicates an invalid console output mode.
DWORD dwOriginalOutMode = 0xffffffff;   ///< Stores the original console output mode.
HANDLE hOut = INVALID_HANDLE_VALUE;     ///< Handle to the console output.
#endif

/// <summary>
/// Called by atexit() on program termination to restore the video mode.
/// </summary>
static void _restoreVTMode(void)
{
#ifdef _MSC_VER
    if (dwOriginalOutMode != INVALID_MODE && hOut != INVALID_HANDLE_VALUE)
    {
        SetConsoleMode(hOut, dwOriginalOutMode);
    }

#endif
}


///////////////////////////////////////////////////////////////////////////////
// enableVTMode()
///////////////////////////////////////////////////////////////////////////////
void enableVTMode()
{
    atexit(_restoreVTMode);

#ifdef _MSC_VER
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        if (!GetConsoleMode(hOut, &dwOriginalOutMode))
        {
            dwOriginalOutMode = INVALID_MODE;
            DWORD lastError = GetLastError();
            printf("Failed to get the Console output's original mode (code = 0x%x).\n", lastError);
        }
        else
        {
            DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
            if (!SetConsoleMode(hOut, dwOutMode))
            {
                DWORD lastError = GetLastError();
                printf("Failed to enable the Console output's virtual terminal mode (code = 0x%x).\n", lastError);
            }
        }
    }
    else
    {
        printf("Failed to get the Console's output handle.\n");
    }
#endif
}
