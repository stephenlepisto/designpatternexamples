## @file
#  @brief
#  Defines the main() function that
#  starts everything by instantiating the Program class and calling Program.Run().
#
#  @namespace DesignPatternExamples_python
#  The DesignPatternExamples_python package, containing 20 examples of design
#  patterns, each in their own namespace.


# For the DesignPatternExamples_python namespace
import sys
from .program import Program

## Main entry point into this example program.
def main():
    prog = Program()
    args = []
    for index in range(1, len(sys.argv)):
        args.append(sys.argv[index])
    return prog.Run(args)


if __name__ == "__main__":
    sys.exit(main())
