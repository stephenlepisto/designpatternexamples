/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.EnableVTModeForWindowsConsole "EnableVTModeForWindowsConsole"
/// class to enable virtual terminal processing in the Windows terminal as
/// used in the @ref decorator_pattern "Decorator pattern".

using System;
using System.IO;
using System.Runtime.InteropServices;

namespace DesignPatternExamples_csharp
{
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
    /// <remarks>This class is expected to be used with a using() statement
    /// so the dispose() method is automatically called.
    /// </remarks>
    internal class EnableVTModeForWindowsConsole : IDisposable
    {
        IntPtr hStdOut;
        uint originalOutConsoleMode;
        private bool disposedValue;

        /// <summary>
        /// Constructor that enables the virtual terminal processing for the
        /// current console output.
        /// </summary>
        public EnableVTModeForWindowsConsole()
        {
            originalOutConsoleMode = INVALID_MODE;
            hStdOut = (IntPtr)INVALID_HANDLE_VALUE;
            // If we running on Windows then change the mode
            if (Path.DirectorySeparatorChar == '\\')
            {
                hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                if (hStdOut != (IntPtr)INVALID_HANDLE_VALUE)
                {
                    if (GetConsoleMode(hStdOut, out uint originalOutConsoleMode))
                    {
                        uint outConsoleMode = originalOutConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                        SetConsoleMode(hStdOut, outConsoleMode);
                    }
                }
            }
        }

        internal const ulong INVALID_HANDLE_VALUE = 0xffffffffffffffff;
        internal const uint INVALID_MODE = 0xffffffff;
        internal const int STD_OUTPUT_HANDLE = -11;
        internal const uint ENABLE_VIRTUAL_TERMINAL_PROCESSING = 0x0004;

        // These should not be called or otherwise referenced if not running
        // on Windows.
        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern IntPtr GetStdHandle(int nStdHandle);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool SetConsoleMode(IntPtr hConsoleHandle, uint mode);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern bool GetConsoleMode(IntPtr handle, out uint mode);

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    if (originalOutConsoleMode != INVALID_MODE)
                    {
                        SetConsoleMode(hStdOut, originalOutConsoleMode);
                    }
                }

                disposedValue = true;
            }
        }

        ~EnableVTModeForWindowsConsole()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: false);
        }

        public void Dispose()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
    }

}

