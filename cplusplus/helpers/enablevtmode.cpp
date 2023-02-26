#ifdef _MSC_VER
#include <iostream>
#include <windows.h>
#endif

namespace // Anonymous
{

#ifdef _MSC_VER
    /// <summary>
    /// Enables the virtual terminal processing mode on the current Windows
    /// Console.  When the program ends, the state of the processing mode is
    /// restored to what it was before we got to it.
    /// 
    /// This is for Windows only.  Although the mode is enabled in all kinds of
    /// Windows console windows (terminal, powershell, etc.), only the Windows
    /// Command Prompt needs it; but it doesn't hurt to set it on the others
    /// (it's already set on those others).
    /// </summary>
    /// <remarks>Using a class in this case to set the mode in the constructor
    /// and restoring the mode in the destructor.  This ensures the mode is
    /// restored no matter how the application exits.</remarks>
    class EnableVTMode
    {
    private:
        const DWORD INVALID_MODE = 0xffffffff;

    private:
        DWORD dwOriginalOutMode;
        HANDLE hOut;
    public:
        EnableVTMode()
            : dwOriginalOutMode(INVALID_MODE)
            , hOut(INVALID_HANDLE_VALUE)
        {
            hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
            if (hOut != INVALID_HANDLE_VALUE)
            {
                if (!::GetConsoleMode(hOut, &dwOriginalOutMode))
                {
                    dwOriginalOutMode = INVALID_MODE;
                    std::cout << "Failed to get the Console output's original mode." << std::endl;
                }
                else
                {
                    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
                    if (!SetConsoleMode(hOut, dwOutMode))
                    {
                        std::cout << "Failed to enable the Console output's virtual terminal mode." << std::endl;
                    }
                }
            }
            else
            {
                std::cout << "Failed to get the Console's output handle." << std::endl;
            }
        }

        ~EnableVTMode()
        {
            if (dwOriginalOutMode != INVALID_MODE)
            {
                ::SetConsoleMode(hOut, dwOriginalOutMode);
            }
        }
    };

#endif

} // end anonymous namespace

namespace Helpers
{
    /// <summary>
    /// On Windows, enable the virtual terminal processing mode on the Console's
    /// output handle.  On all other operating systems, this function does
    /// nothing.
    /// </summary>
    void enableVTMode()
    {
#ifdef _MSC_VER
        static EnableVTMode enableVTMode;
#endif
    }

} // end namespace
