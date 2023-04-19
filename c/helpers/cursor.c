/// @file
/// @brief
/// Implementation of the setcursorposition() and getcursorposition() functions
/// for manipulating the cursor position on Windows terminals.

#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#include <windows.h>
#endif

#include "cursor.h"
#include "split.h"

#ifdef _MSC_VER
static HANDLE hStdIn = INVALID_HANDLE_VALUE;
static HANDLE hStdOut = INVALID_HANDLE_VALUE;
static DWORD inputMode = 0;
#endif

/// <summary>
/// Initialize the console.
/// </summary>
static void _init_console_mode()
{
#ifdef _MSC_VER
    if (hStdOut == INVALID_HANDLE_VALUE)
    {
        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdOut == INVALID_HANDLE_VALUE)
        {
            DWORD lastError = GetLastError();
            printf("GetStdHandle(STD_OUTPUT_HANDLE) failed: code = 0x%x\n", lastError);
        }
    }
    if (hStdIn == INVALID_HANDLE_VALUE)
    {
        hStdIn = GetStdHandle(STD_INPUT_HANDLE);
        if (hStdIn != INVALID_HANDLE_VALUE)
        {
            GetConsoleMode(hStdIn, &inputMode);
        }
        else
        {
            DWORD lastError = GetLastError();
            printf("GetStdHandle(STD_INPUT_HANDLE) failed: code = 0x%x\n", lastError);
        }
    }
#endif
}

/// <summary>
/// Disable echoing of input and disable line input mode (where the Enter
/// key must be entered to complete input).
/// </summary>
static void _disableInputEcho()
{
#ifdef _MSC_VER
    _init_console_mode();
    if (hStdIn != INVALID_HANDLE_VALUE)
    {
        DWORD newMode = inputMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
        if (!SetConsoleMode(hStdIn, newMode))
        {
            DWORD lastError = GetLastError();
            printf("SetConsoleMode(hStdIn, newMode) failed: code = 0x%x\n", lastError);
        }
    }
#endif
}

/// <summary>
/// Enable echoing of input.
/// </summary>
static void _enableInputEcho()
{
#ifdef _MSC_VER
    _init_console_mode();
    if (hStdIn != INVALID_HANDLE_VALUE)
    {
        if (!SetConsoleMode(hStdIn, inputMode))
        {
            DWORD lastError = GetLastError();
            printf("SetConsoleMode(hStdIn, inputMode) failed: code = 0x%x\n", lastError);
        }
    }
#endif
}



void setcursorposition(int row, int column)
{
    printf("\x1b[%d;%dH", row, column);
    fflush(stdout);
}

void getcursorposition(int* row, int* column)
{
    if (row != NULL && column != NULL)
    {
        _disableInputEcho();
        printf("\x1b[6n");
        fflush(stdout);
        char buffer[16] = { 0 };
        // Must specify a delimiter, otherwise will block until eof (ctrl-Z).
        int c = 0;
        int bufferIndex = 0;
        while (c != 'R' && c != EOF)
        {
            c = getc(stdin);
            buffer[bufferIndex] = (char)c;
            bufferIndex++;
        }
        // Expecting ESC [ <r> ; <c> R (no spaces)
        if (strlen(buffer) > 2 && buffer[0] == '\x1b' && buffer[1] == '[')
        {
            SplitList elements = { 0 };
            split(buffer, "[;R", &elements);
            if (elements.strings_count >= 3)
            {
                *row = (int)_strtoi64(elements.strings[1], NULL, 0);
                *column = (int)_strtoi64(elements.strings[2], NULL, 0);
            }
            SplitList_Clear(&elements);
        }
        _enableInputEcho();
    }
}
