
/// @file
/// @brief
/// Implementation of the Decorator_Exercise() function as used in the 
/// @ref decorator_pattern.

#include <iostream>

#include "helpers/formatstring.h"

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
            << Helpers::formatstring("  base Text element: \"%s\"", baseElement->Render().c_str())
            << std::endl;
        std::cout
            << Helpers::formatstring("  Decorated element: \"%s\"", wrappedElement->Render().c_str())
            << std::endl;

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Decorator in C++]


} // end namespace
