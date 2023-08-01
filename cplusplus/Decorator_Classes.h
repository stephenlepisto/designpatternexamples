/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::IRenderElement "IRenderElement"
/// interface, @ref DesignPatternExamples_cpp::Decorator "Decorator" base class,
/// @ref DesignPatternExamples_cpp::TextElement "TextElement" class, and the
/// concrete decorator classes used in the @ref decorator_pattern.

#pragma once
#ifndef __DECORATOR_CLASSES_H__
#define __DECORATOR_CLASSES_H__

#include <string>
#include <memory>

#include "helpers/argumentnull_error.h"
#include "helpers/formatstring.h"

namespace DesignPatternExamples_cpp
{

    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents an element that can be rendered in text.  All decorators
    /// and the core element class implement this interface.
    /// </summary>
    struct IRenderElement
    {
        /// <summary>
        /// An alias to simplify syntax for this shared pointer.
        /// </summary>
        using shared_ptr_t = std::shared_ptr<IRenderElement>;

        virtual ~IRenderElement() {}

        /// <summary>
        /// Render this element as a string.
        /// </summary>
        /// <returns>A string containing the rendering of the element.</returns>
        virtual std::string Render() = 0;
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the base class of all decorators and is responsible for
    /// handling the wrapped element being decorated.
    /// </summary>
    class Decorator : public IRenderElement
    {
    private:
        IRenderElement::shared_ptr_t _wrappedElement;
    
    public:
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="element">The IRenderElement to be wrapped and
        /// decorated.</param>
        Decorator(IRenderElement::shared_ptr_t element)
            : _wrappedElement(element)
        {
            if (!_wrappedElement)
            {
                throw Helpers::argumentnull_error("element",
                    "The element being decorated cannot be null.");
            }
        }


        /// <summary>
        /// Render the wrapped element.
        /// </summary>
        /// <returns>A string containing the rendered wrapped element.</returns>
        std::string Render()
        {
            return _wrappedElement->Render();
        }
    };

    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the WhiteBackground decorator, which changes the background
    /// color of the wrapped element to white.
    /// </summary>
    class WhiteBackgroundDecorator : public Decorator
    {
    public:

        /// <summary>
        /// Constructor that wraps the specified element.
        /// </summary>
        /// <param name="element">The IRenderElement to be decorated.
        /// Cannot be null.</param>
        /// <exception cref="argumentnull_error">The element being decorated
        /// cannot be null.</exception>
        WhiteBackgroundDecorator(IRenderElement::shared_ptr_t element)
            : Decorator(element)
        {
        }

        // IRenderElement Members

        /// <summary>
        /// Render the wrapped element with decorations.
        /// </summary>
        /// <returns>A string containing the decorated rendered element.</returns>
        std::string Render()
        {
            return Helpers::formatstring("\x1b[47m%s\x1b[49m", Decorator::Render().c_str());
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Underline decorator, which underlines the wrapped
    /// content.
    /// </summary>
    class UnderlineDecorator : public Decorator
    {
    public:

        /// <summary>
        /// Constructor that wraps the specified element.
        /// </summary>
        /// <param name="element">The IRenderElement to be decorated.
        /// Cannot be null.</param>
        /// <exception cref="argumentnull_error">The element being decorated
        /// cannot be null.</exception>
        UnderlineDecorator(IRenderElement::shared_ptr_t element)
            : Decorator(element)
        {
        }

        // IRenderElement Members

        /// <summary>
        /// Render the wrapped element with decorations.
        /// </summary>
        /// <returns>A string containing the decorated rendered element.</returns>
        std::string Render()
        {
            return Helpers::formatstring("\x1b[4m%s\x1b[24m", Decorator::Render().c_str());
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the RedForeground decorator, which renders the wrapped
    /// content as red text.
    /// </summary>
    class RedForegroundDecorator : public Decorator
    {
    public:

        /// <summary>
        /// Constructor that wraps the specified element.
        /// </summary>
        /// <param name="element">The IRenderElement to be decorated.
        /// Cannot be null.</param>
        /// <exception cref="argumentnull_error">The element being decorated
        /// cannot be null.</exception>
        RedForegroundDecorator(IRenderElement::shared_ptr_t element)
            : Decorator(element)
        {
        }

        // IRenderElement Members

        /// <summary>
        /// Render the wrapped element with decorations.
        /// </summary>
        /// <returns>A string containing the decorated rendered element.</returns>
        std::string Render()
        {
            return Helpers::formatstring("\x1b[31m%s\x1b[39m", Decorator::Render().c_str());
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the core element that can be decorated.  Note that this
    /// class implements the IRenderElement but otherwise has no knowledge
    /// of any of the decorators that might be applied.
    /// 
    /// This class wraps a string and does nothing other than return the
    /// string.  This way, this class can be decorated because it implements
    /// the IRenderElement interface.
    /// </summary>
    class TextElement : public IRenderElement
    {
    private:
        /// <summary>
        /// The raw text at the center of all decorators.
        /// </summary>
        std::string _elementText;

    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="element">The text to be rendered.</param>
        TextElement(std::string element)
        {
            _elementText = element;
        }

        // IRenderElement Members

        /// <summary>
        /// Render this element as a string.
        /// </summary>
        /// <returns>A string containing the rendering of the element.</returns>
        std::string Render()
        {
            return _elementText;
        }
    };

} // end namespace

#endif // __DECORATOR_CLASSES_H__
