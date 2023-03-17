## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.proxy.proxy_exercise.Proxy_Exercise "Proxy_Exercise"()
#  function as used in the @ref proxy_pattern.

from .proxy_class import Proxy_Classes_Container

##  Example of using the @ref proxy_pattern.
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

# ! [Using Proxy in Python]
def Proxy_Exercise():
    print()
    print("Proxy Exercise")

    print("  Getting proxy object...")
    proxyObject = Proxy_Classes_Container.CreateProxy()

    print("  Calling Dowork() on proxy...")
    output = proxyObject.DoWork("Initial call")
    print("  Output from proxy = \"{0}\"".format(output))

    print("  Calling Dowork() on proxy...")
    output = proxyObject.DoWork("Second call")
    print("  Output from proxy = \"{0}\"".format(output))

    print("  Calling Dowork() on proxy...")
    output = proxyObject.DoWork("Third call");
    print("  Output from proxy = \"{0}\"".format(output))

    print("  Done.")
# ! [Using Proxy in Python]
