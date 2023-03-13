## Main entry point for the DesignPatternExamples_python package.  Uses the
#  definition of main() from the __init__.py file.

# The following is used during debugging; VS2022 does not allow for launching
# Python package in such a way as to set the package name, which allows relative
# import to work.  The work-around is to force the package name here.  Then
# the debugger can launch __main__.py with a working directory set to "../../".
__package__ = "python.DesignPatternExamples_python" if not __package__ else __package__

import sys
from . import main
from .enablevtmode import EnableVTMode

sys.exit(EnableVTMode(main))
