
/// @file
/// @brief
/// Implementation of the Proxy_Exercise() function as used in the 
/// @ref proxy_pattern.

#include <iostream>

#include "helpers/formatstring.h"

#include "Proxy_Exercise.h"
#include "Proxy_Class.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref proxy_pattern "Proxy" design pattern.
    /// 
    /// The Proxy pattern is used when a large or expensive object cannot be
    /// represented directly in the program, typically because the object is
    /// in another process or even another system altogether.
    /// 
    /// In this exercise, a Proxy class implements the same interface as the
    /// Real class, making the Proxy class look like the Real class.  Calls
    /// made on the Proxy class are passed to the Real class where the work
    /// is actually done (in this case, a munged string with the text
    /// "Real class received 'xxxx'".
    /// 
    /// The only difference in output here is one additional line for the
    /// first call showing the real class being instantiated.  The subsequent
    /// calls do not show this line.
    /// </summary>
    // ! [Using Proxy in C++]
    void Proxy_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Proxy Exercise" << std::endl;

        std::cout << "  Getting proxy object..." << std::endl;
        std::unique_ptr<IWorkByProxy> proxyObject = Proxy_Classes_Container::CreateProxy();

        std::cout << "  Calling Dowork() on proxy..." << std::endl;
        std::string output = proxyObject->DoWork("Initial call");
        std::cout << Helpers::formatstring("  Output from proxy = \"%s\"", output.c_str()) << std::endl;

        std::cout << "  Calling Dowork() on proxy..." << std::endl;
        output = proxyObject->DoWork("Second call");
        std::cout << Helpers::formatstring("  Output from proxy = \"%s\"", output.c_str()) << std::endl;

        std::cout << "  Calling Dowork() on proxy..." << std::endl;
        output = proxyObject->DoWork("Third call");
        std::cout << Helpers::formatstring("  Output from proxy = \"%s\"", output.c_str()) << std::endl;

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Proxy in C++]

} // end namespace
