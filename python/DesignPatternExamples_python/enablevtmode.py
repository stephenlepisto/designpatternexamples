## @file
#  @brief
#  Defines a wrapper function that enable virtual terminal processing for
#  Windows Command Prompt.
#
#  This function is intended to wrap the call to main() so it can restore the
#  mode on exit.  How to use:
#  ~~~~~~~~~~~~~~~~~~~~~~~{.py}
#  from .enablevtmode import EnableVTMode
#
#  def main() -> int:
#    return 0
#
#  sys.exit(EnableVTMode(main))
#  ~~~~~~~~~~~~~~~~~~~~~~~

## Value representing the Standard Output Handle in the Windows Console
STD_OUTPUT_HANDLE = -11
## Flag that, when set, enables virtual terminal processing and thus support for
#  ANSI escape code handling.
ENABLE_VIRTUAL_TERMINAL_PROCESSING = 0x0004

## Holds the original mode for Standard Output in the Windows Console so it can
#  be restored later on.
originalConsoleMode = None

# Try to import ctypes and get the kernel32 DLL.  If neither is possible, the
# rest of the code in this module does nothing.
try:
    import ctypes
    kernel32 = ctypes.windll.kernel32
except:
    # ctypes does not exist, assume not on Windows
    kernel32 = None

## If we are on Windows (as indicated by the presence of the Kernel32 DLL),
#  set the virtual terminal processing flag on the standard output for the
#  Windows Console.
def _SetVTMode() -> None:
    if kernel32:
        global originalConsoleMode
        stdOutput = kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
        oldMode = ctypes.c_uint32(0)
        if kernel32.GetConsoleMode(stdOutput, ctypes.byref(oldMode)):
            originalConsoleMode = oldMode.value
            newMode = originalConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING
            kernel32.SetConsoleMode(stdOutput, newMode)


## If we are on Windows (as indicated by the presence of the Kernel32 DLL),
#  restore the standard output mode for the Windows Console.
def _RestoreVTMode() -> None:
    if kernel32 and originalConsoleMode is not None:
        stdOutput = kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
        kernel32.SetConsoleMode(stdOutput, originalConsoleMode)


## Wrap the given function with enabling and disabling the virtual terminal
#  processing for a Windows Console.  The processing is disabled regardless
#  of the exit state of the function.
#
#  This is generally intended to wrap a main() function like this:
#  ~~~~~~~~~~~~~~~~~~~~~~~{.py}
#  sys.exit(EnableVTMode(main))
#  ~~~~~~~~~~~~~~~~~~~~~~~
def EnableVTMode(function : callable):
    _SetVTMode()
    try:
        return function()
    finally:
        _RestoreVTMode()
