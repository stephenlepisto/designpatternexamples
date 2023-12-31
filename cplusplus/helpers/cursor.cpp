/// @file
/// @brief
/// Implementation of the @ref Helpers::setcursorposition "setcursorposition()" and
/// @ref Helpers::getcursorposition "getcursorposition()" functions for manipulating
/// the cursor position on Windows terminals.

#include <iostream>
#include <string>
#include <vector>

#ifdef _MSC_VER
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include "_countof.h"
#include "cursor.h"
#include "split.h"
#include "formatstring.h"

namespace
{
    bool inputEchoDisabled = false;
#ifdef _MSC_VER
    HANDLE hStdIn = INVALID_HANDLE_VALUE;
    HANDLE hStdOut = INVALID_HANDLE_VALUE;
    DWORD inputMode = 0;

    /// <summary>
    /// Initialize the console.
    /// </summary>
    void _init_console_mode()
    {
        if (hStdOut == INVALID_HANDLE_VALUE)
        {
            hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (hStdOut == INVALID_HANDLE_VALUE)
            {
                DWORD lastError = ::GetLastError();
                std::cout << Helpers::formatstring("GetStdHandle(STD_OUTPUT_HANDLE) failed: code = 0x%x", lastError) << std::endl;
            }
        }
        if (hStdIn == INVALID_HANDLE_VALUE)
        {
            hStdIn = GetStdHandle(STD_INPUT_HANDLE);
            if (hStdIn != INVALID_HANDLE_VALUE)
            {
                ::GetConsoleMode(hStdIn, &inputMode);
            }
            else
            {
                DWORD lastError = ::GetLastError();
                std::cout << Helpers::formatstring("GetStdHandle(STD_INPUT_HANDLE) failed: code = 0x%x", lastError) << std::endl;
            }
        }
    }
#else
    static struct termios oldt, newt;
#endif

    /// <summary>
    /// Disable echoing of input and disable line input mode (where the Enter
    /// key must be entered to complete input).
    /// </summary>
    void _disableInputEcho()
    {
#ifdef _MSC_VER
        _init_console_mode();
        if (hStdIn != INVALID_HANDLE_VALUE)
        {
            DWORD newMode = inputMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
            if (!::SetConsoleMode(hStdIn, newMode))
            {
                DWORD lastError = ::GetLastError();
                std::cout << Helpers::formatstring("SetConsoleMode(hStdIn, newMode) failed: code = 0x%x", lastError) << std::endl;
            }
        }
#else
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
        inputEchoDisabled = true;
    }

    /// <summary>
    /// Enable echoing of input.
    /// </summary>
    void _enableInputEcho()
    {
#ifdef _MSC_VER
        _init_console_mode();
        if (hStdIn != INVALID_HANDLE_VALUE)
        {
            if (!::SetConsoleMode(hStdIn, inputMode))
            {
                DWORD lastError = ::GetLastError();
                std::cout << Helpers::formatstring("SetConsoleMode(hStdIn, inputMode) failed: code = 0x%x", lastError) << std::endl;
            }
        }
#else
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
        inputEchoDisabled = false;
    }

} // end anonymous namespace


namespace Helpers
{
    ///////////////////////////////////////////////////////////////////////////
    // disableinputecho()
    ///////////////////////////////////////////////////////////////////////////
    void disableinputecho()
    {
        if (!inputEchoDisabled)
        {
            _disableInputEcho();
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    // enableinputecho()
    ///////////////////////////////////////////////////////////////////////////
    void enableinputecho()
    {
        if (inputEchoDisabled)
        {
            _enableInputEcho();
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    // setcursorposition()
    ///////////////////////////////////////////////////////////////////////////
    void setcursorposition(int row, int column)
    {
        std::cout << "\x1b[" << row << ";" << column << "H";
        std::cout.flush();
    }

    ///////////////////////////////////////////////////////////////////////////
    // getcursorposition()
    ///////////////////////////////////////////////////////////////////////////
    void getcursorposition(int *row, int *column)
    {
        if (row != nullptr && column != nullptr)
        {
            // Don't disable input echo if it is already disabled.
            bool wasInputEchoDisabled = inputEchoDisabled;
            if (!wasInputEchoDisabled)
            {
                _disableInputEcho();
            }

            std::cout << "\x1b[6n";
            std::cout.flush();
            char buffer[16]{ 0 };
            // Must specify a delimiter, otherwise will block until eof (ctrl-Z).
            std::cin.get(buffer, _countof(buffer), 'R');
            int lastChar = std::cin.get(); // Retrieve the delimiter
            std::string input(buffer);
            input += (char)lastChar;
            // Expecting ESC [ <r> ; <c> R (no spaces)
            if (input.size() > 2 && input[0] == '\x1b' && input[1] == '[')
            {
                std::vector<std::string> elements = split(input, "[;R");
                if (elements.size() >= 3)
                {
                    *row = std::stoi(elements[1], nullptr);
                    *column = std::stoi(elements[2], nullptr);
                }
            }
            if (!wasInputEchoDisabled)
            {
                _enableInputEcho();
            }
        }
    }

} // end namespace
