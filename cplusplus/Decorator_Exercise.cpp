
/// @file
/// @brief
/// Implementation of the Decorator_Exercise() function as used in the 
/// @ref decorator_pattern "Decorator pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "Decorator_Exercise.h"
#include "Decorator_Classes.h"


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref decorator_pattern "Decorator" design pattern.
    /// 
    /// The Decorator pattern is used when a class instance at run time needs
    /// to have its behavior altered.  This is supported by providing wrapper
    /// classes called decorators that take instances of the IRenderElement
    /// interface.  All elements look the same and can therefore recursively
    /// wrap other decorators.  The base element never wraps anything and
    /// decorators must ultimately wrap a non-decorator class to be of any
    /// use.
    /// </summary>
    // ! [Using Decorator in C++]
    void Decorator_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Decorator Exercise" << std::endl;

        IRenderElement::shared_ptr_t baseElement;
        baseElement = std::make_shared<TextElement>("This is raw text");

        // Wrap the base element in three decorators.
        IRenderElement::shared_ptr_t wrappedElement =
            std::make_shared<WhiteBackgroundDecorator>(
                std::make_shared<UnderlineDecorator>(
                    std::make_shared<RedForegroundDecorator>(baseElement)));

        // Now render the elements to the console.
        std::cout
            << std::format("  base Text element: \"{0}\"", baseElement->Render())
            << std::endl;
        std::cout
            << std::format("  Decorated element: \"{0}\"", wrappedElement->Render())
            << std::endl;

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Decorator in C++]


} // end namespace
