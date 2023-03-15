## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.flyweight.flyweight_helpers.Helpers "Helpers"
#  class as used in the @ref flyweight_pattern.

import re
import sys
import time


## Windows Kernel32 identifier for standard input
STD_INPUT_HANDLE = -10
## Windows indicator of an invalid handle
INVALID_HANDLE_VALUE = -1
## Flag to enable buffering standard input until Enter is pressed
ENABLE_LINE_INPUT = 0x0002
## Flag to enable echoing everything in standard input
ENABLE_ECHO_INPUT = 0x0004

## Ctrl-Z ASCII code, used for end of file marker
ASCII_CTRL_Z = '\x1a'
## ESC ASCII code
ASCII_ESC = '\x1b'


## Try to import ctypes and get the kernel32 DLL along with the Microsoft C
#  Runtime.  If neither is possible, the rest of the code in this module does
#  nothing.
try:
    import ctypes
    kernel32 = ctypes.windll.kernel32
    import msvcrt  # Only on Windows
except:
    # ctypes does not exist, assume not on Windows
    kernel32 = None
    # And, therefore, the Microsoft C Runtime does not exist either.
    msvcrt = None

## Class containing a number of helper methods for use in the
#  @ref flyweight_pattern example.
#
#  Instantiate this class then call the methods.  For example:
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~{.py}
#  helpers = Helpers()
#  helpers.sleep(10)
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Helpers:
    ## Constructor.
    def __init__(self) -> None:
        self._hStdIn = INVALID_HANDLE_VALUE
        self._inputMode = 0

    ## @var _hStdIn
    #       Handle to the Windows standard input (Windows only)
    #  @var _inputMode
    #       The initial mode controlling the standard input (Windows only)

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
        print("{}[{};{}H".format(ASCII_ESC, row, column))

    ## Retrieve the current cursor position in the console window.
    #
    # @returns
    #   Returns tuple containing the column,row.
    def getcursorposition(self) -> tuple:
        row = 0
        column = 0
        self._disableInputEcho()
        try:
            # Send, via standard out, the ANSI string to request the current cursor
            # position.  The position will be returned in standard input.
            sys.stdout.write("{}[6n".format(ASCII_ESC))
            sys.stdout.flush()
            # We are expecting in the input buffer the following characters (minus
            # the spaces:
            # ESC [ <r> ; <c> R
            # Where <r> and <c> are 1 to n decimal digits specifying the row and
            # column position, respectively.
            # We know there are at least 6 characters waiting in the input queue
            # so read them one at a time until we reach the end (signified by 'R').
            #
            # (Note: This could block if there is nothing in the standard input,
            # which could happen if the "get cursor position" ANSI control sequence
            # (or any ANSI control sequence) is not supported.  Use Ctrl-Z on the
            # keyboard to release the block.)
            inputbuffer = []
            while True:
                c = sys.stdin.read(1)
                inputbuffer.append(c)
                if c == 'R' or c == ASCII_CTRL_Z:
                    break
            buffer = ''.join(inputbuffer)
            if len(buffer) > 2 and buffer[0] == ASCII_ESC and buffer[1] == '[':
                elements = re.split(".\[([0-9]+);([0-9]+)R", buffer)
                if len(elements) >= 3:
                    row = int(elements[1])
                    column = int(elements[2])
        finally:
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
    #  The expectation is this is called only if the
    #  @ref DesignPatternExamples_python.flyweight.flyweight_helpers.Helpers.checkforkey "checkforkey"()
    #  method indicates a key is available in the standard input.
    #
    #  @returns
    #     Returns the ASCII for the key pressed.
    def readkey(self) -> int:
        self._disableInputEcho()
        try:
            retval = sys.stdin.read(1)
        finally:
            self._enableInputEcho()
        return retval
