## @file
# @brief
# Implementation of the Proxy_Exercise() function as used in the 
# @ref proxy_pattern "Proxy pattern".


##  Example of using the @ref proxy_pattern "Proxy" design pattern.
#  
#  The Proxy pattern is used when a large or expensive object cannot be
#  represented directly in the program, typically because the object is
#  in another process or even another system altogether.
#  
#  In this exercise, a Proxy class implements the same interface as the
#  Real class, making the Proxy class look like the Real class.  Calls
#  made on the Proxy class are passed to the Real class where the work
#  is actually done (in this case, a munged string with the text
#  "Real class received 'xxxx'".
#  
#  The only difference in output here is one additional line for the
#  first call showing the real class being instantiated.  The subsequent
#  calls do not show this line.
##! [Using Proxy in Python]
def Proxy_Exercise():
    print()
    print("Proxy Exercise")

    print("  Done.")
##! [Using Proxy in Python]