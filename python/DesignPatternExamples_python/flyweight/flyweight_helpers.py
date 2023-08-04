## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.flyweight.flyweight_helpers.Helpers "Helpers"
#  class as used in the @ref flyweight_pattern.

import re
import select
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


# For Windows, try to import the Microsoft C Runtime (mscvrt) and ctypes to get
# the kernel32 DLL.  If neither is possible, the rest of the Windows-specific
# code in this module does nothing.
try:
    import msvcrt  # Only on Windows
    import ctypes
    kernel32 = ctypes.windll.kernel32
    termios = None
except:
    # The Microsoft C Runtime does not exist, so assume Windows kernel32
    # doesn't exist.
    msvcrt = None
    kernel32 = None
    try:
        import termios # Assume we are on Linux
    except:
        print("  Error! No termios or msvcrt.  Cannot check for keys or get cursor position.")


## Class for temporarily disabling echoing of characters sent to standard in.
#
#  Use this class like this:
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~{.py}
#  with DisableInputEcho():
#     pass
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~
class DisableInputEcho():
    def __init__(self):
        if termios:
            self.old_settings = None
        elif kernel32:
            self._inputMode = None
            self._hStdIn = kernel32.GetStdHandle(STD_INPUT_HANDLE)
            if self._hStdIn != INVALID_HANDLE_VALUE:
                oldMode = ctypes.c_uint32(0)
                if kernel32.GetConsoleMode(self._hStdIn, ctypes.byref(oldMode)):
                    self._inputMode = oldMode.value
            else:
                lastError = kernel32.GetLastError()
                print("GetStdHandle(STD_INPUT_HANDLE) failed: code = {:x}".format(lastError))

    def disable_input_echo(self):
        if termios:
            stdin_fd = sys.stdin.fileno()
            self.old_settings = termios.tcgetattr(stdin_fd)
            new_settings = termios.tcgetattr(stdin_fd);
            new_settings[3] = new_settings[3] & ~termios.ICANON & ~termios.ECHO
            termios.tcsetattr(stdin_fd, termios.TCSANOW, new_settings)
        elif kernel32:
            if self._hStdIn != INVALID_HANDLE_VALUE:
                newMode = self._inputMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT)
                if not kernel32.SetConsoleMode(self._hStdIn, newMode):
                    lastError = kernel32.GetLastError()
                    print("SetConsoleMode(hStdIn, newMode) failed: code = {:x}".format(lastError))

    def enable_input_echo(self):
        if termios:
            stdin_fd = sys.stdin.fileno()
            if self.old_settings:
                termios.tcsetattr(stdin_fd, termios.TCSANOW, self.old_settings)
                self.old_settings = None
        elif kernel32:
            if self._hStdIn != INVALID_HANDLE_VALUE and self._inputMode is not None:
                if not kernel32.SetConsoleMode(self._hStdIn, self._inputMode):
                    lastError = kernel32.GetLastError()
                    print("SetConsoleMode(hStdIn, inputMode) failed: code = {:x}".format(lastError))

    def __enter__(self):
        self.disable_input_echo()

    def __exit__(self, *args):
        self.enable_input_echo()



## Class containing a number of helper methods for use in the
#  @ref flyweight_pattern example.
#
#  Instantiate this class then call the methods.  For example:
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~{.py}
#  helpers = Helpers()
#  helpers.sleep(10)
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Helpers:

    ## Move the text cursor to the specified screen coordinates.
    #
    # @param row
    #        Row index from top, starting at 1.
    # @param column
    #        Column index from left, starting at 1
    def setcursorposition(self, row: int, column: int) -> None:
        print("{}[{};{}H".format(ASCII_ESC, row, column), end="")
        sys.stdout.flush()

    ## Retrieve the current cursor position in the console window.
    #
    #  @returns
    #   Returns tuple containing the column,row, relative to the upper left
    #   corner of the window.  Position starts at 1,1
    def getcursorposition(self) -> tuple:
        row = 0
        column = 0
        with DisableInputEcho():
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
        else:
            dr,dw,de = select.select([sys.stdin], [], [], 0)
            if not dr == []:
                return True
        return False


    ## Read a key from the keyboard, blocking if no key is pressed.
    #  The expectation is this is called only if the
    #  @ref DesignPatternExamples_python.flyweight.flyweight_helpers.Helpers.checkforkey "checkforkey"()
    #  method indicates a key is available in the standard input.
    #
    #  @returns
    #     Returns the ASCII for the key pressed.
    def readkey(self) -> int:
        return sys.stdin.read(1)
