## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.facade.facade_exercise.Facade_Exercise "Facade_Exercise"()
# function as used in the @ref facade_pattern.


##  Example of using the @ref facade_pattern.
#  
#  The Facade pattern is used when a simplified version of an
#  interface on a complicated sub-system is needed in situations
#  where the whole complicated sub-system does not need to be
#  exposed.
#  
#  In this example, the complicated subsystem is a representation of
#  a device network complete with scan chains, device idcodes, and device
#  devices that can be selected and deselected.  The Facade exposed
#  by this complex network exposes only the scan chain, getting
#  device idcodes based on an index into those scan chains, resetting
#  the scan chains and selecting a device to appear in the scan
#  chain.

# ! [Using Facade in Python]
def Facade_Exercise():
    print()
    print("Facade Exercise")

    print("  Done.")
# ! [Using Facade in Python]
