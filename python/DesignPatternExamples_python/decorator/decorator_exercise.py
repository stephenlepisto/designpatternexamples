## @file
# @brief
# Implementation of the Decorator_Exercise() function as used in the 
# @ref decorator_pattern "Decorator pattern".


## Example of using the @ref decorator_pattern "Decorator" design pattern.
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

    print("  Done.")
# ! [Using Decorator in Python]
