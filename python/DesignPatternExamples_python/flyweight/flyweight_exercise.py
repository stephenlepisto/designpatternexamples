## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.flyweight.flyweight_exercise.Flyweight_Exercise "Flyweight_Exercise"()
# function as used in the @ref flyweight_pattern.


##  Example of using the @ref flyweight_pattern.
#  
#  The Flyweight pattern is used when a large object needs to be
#  represented by a much lighter weight class, possibly multiple
#  instances of said light-weight class.
#  
#  In this example, a large object is represented by a so-called "big
#  resource" or image (a two-dimensional array of text characters).
#  Flyweight classes that represent position and velocity are
#  attached to the big resource image so they all share the same image
#  but have different positions and velocities.  The image is rendered
#  to a display area through the Flyweight class.  The Flyweight
#  class instances then have their positions updated, bouncing off the
#  edges of the display area 60 times a second.  This continues for
#  1000 iterations or until a key is pressed.

# ! [Using Flyweight in Python]
def Flyweight_Exercise():
    print()
    print("Flyweight Exercise")

    print("  Done.")
# ! [Using Flyweight in Python]
