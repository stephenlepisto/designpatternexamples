## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.decorator.decorator_exercise.Decorator_Exercise "Decorator_Exercise"()
# function as used in the @ref decorator_pattern.

from .decorator_classes import WhiteBackgroundDecorator, UnderlineDecorator, RedForegroundDecorator, TextElement


## Example of using the @ref decorator_pattern.
#  
#  The Decorator pattern is used when a class instance at run time needs
#  to have its behavior altered.  This is supported by providing wrapper
#  classes called decorators that take instances of the IRenderElement
#  interface.  All elements look the same and can therefore recursively
#  wrap other decorators.  The base element never wraps anything and
#  decorators must ultimately wrap a non-decorator class to be of any
#  use.

# ! [Using Decorator in Python]
def Decorator_Exercise():
    print()
    print("Decorator Exercise")

    baseElement = TextElement("This is raw text")

    # Wrap the base element in three decorators.
    wrappedElement = \
        WhiteBackgroundDecorator(
            UnderlineDecorator(
                RedForegroundDecorator(baseElement)
            )
        )

    # Now render the elements to the console.
    print("  base Text element: \"{0}\"".format(baseElement.Render()))
    print("  Decorated element: \"{0}\"".format(wrappedElement.Render()))

    print("  Done.")
# ! [Using Decorator in Python]
