## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.flyweight.flyweight_helpers.Helpers "Helpers"
#  class as used in the @ref flyweight_pattern.

import re
import sys
import time
from io import StringIO

try:
    import msvcrt  # Only on Windows
except:
    msvcrt = None


STD_INPUT_HANDLE = -10
INVALID_HANDLE_VALUE = -1
ENABLE_LINE_INPUT = 0x0002
ENABLE_ECHO_INPUT = 0x0004


# Try to import ctypes and get the kernel32 DLL.  If neither is possible, the
# rest of the code in this module does nothing.
try:
    import ctypes
    kernel32 = ctypes.windll.kernel32
except:
    # ctypes does not exist, assume not on Windows
    kernel32 = None

class Helpers:
    def __init__(self) -> None:
        self._hStdIn = INVALID_HANDLE_VALUE
        self._inputMode = 0

    ## Initialize the console.
    def _init_console_mode(self) -> None:
        if kernel32:
            if self._hStdIn == INVALID_HANDLE_VALUE:
                self._hStdIn = kernel32.GetStdHandle(STD_INPUT_HANDLE)
                if self._hStdIn != INVALID_HANDLE_VALUE:
                    oldMode = ctypes.c_uint32(0)
                    if kernel32.GetConsoleMode(self._hStdIn, ctypes.byref(oldMode)):
                        self._inputMode = oldMode.value
                else:
                    lastError = kernel32.GetLastError()
                    print("GetStdHandle(STD_INPUT_HANDLE) failed: code = {:x}".format(lastError))


    ## Disable echoing of input and disable line input mode (where the Enter
    #  key must be entered to complete input).
    def _disableInputEcho(self) -> None:
        self._init_console_mode()
        if kernel32 and self._hStdIn != INVALID_HANDLE_VALUE:
            newMode = self._inputMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT)
            if not kernel32.SetConsoleMode(self._hStdIn, newMode):
                lastError = kernel32.GetLastError()
                print("SetConsoleMode(hStdIn, newMode) failed: code = {:x}".format(lastError))


    ## Enable echoing of input.
    def _enableInputEcho(self):
        self._init_console_mode()
        if kernel32 and self._hStdIn != INVALID_HANDLE_VALUE:
            if not kernel32.SetConsoleMode(self._hStdIn, self._inputMode):
                lastError = kernel32.GetLastError()
                print("SetConsoleMode(hStdIn, inputMode) failed: code = {:x}".format(lastError))


    ## Move the text cursor to the specified screen coordinates.
    #
    # @param row
    #        Row index from top, starting at 0.
    # @param column
    #        Column index from left, starting at 0
    def setcursorposition(self, row: int, column: int) -> None:
        print("\x1b[{};{}H".format(row, column))

    ## Retrieve the current cursor position in the console window.
    #
    # @returns
    #   Returns tuple containing the column,row.
    def getcursorposition(self) -> tuple:
        row = 0
        column = 0
        if msvcrt:
            self._disableInputEcho()
            sys.stdout.write("\x1b[6n")
            sys.stdout.flush()
            inputbuffer = []
            while True:
                c = msvcrt.getch()
                inputbuffer.append(c.decode())
                if c.decode() == 'R':
                    break
            buffer = ''.join(inputbuffer)
            # Expecting ESC [ <r> ; <c> R (no spaces)
            if len(buffer) > 2 and buffer[0] == '\x1b' and buffer[1] == '[':
                elements = re.split(".\[([0-9]+);([0-9]+)R", buffer)
                if len(elements) >= 3:
                    row = int(elements[1])
                    column = int(elements[2])
            self._enableInputEcho()
        return (column, row)


    ## Sleep for the specified number of milliseconds.
    def sleep(self, milliseconds : int) -> None:
        time.sleep(milliseconds/1000.0)

    ## Determine if a key has been pressed on the keyboard.
    #
    #  @returns
    #     Returns True if a key has been pressed; otherwise, returns False.
    def checkforkey(self) -> bool:
        if msvcrt:
            return msvcrt.kbhit()
        return False


    ## Read a key from the keyboard, blocking if no key is pressed.
    #
    #  @returns
    #     Returns the ASCII for the key pressed.
    def readkey(self) -> int:
        retval = 0
        if msvcrt:
            retval = msvcrt.getch()
            if retval == 0:
                retval = msvcrt.msvcrt
        return retval
