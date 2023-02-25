#pragma once
#ifndef __DECORATOR_CLASSES_H__
#define __DECORATOR_CLASSES_H__

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <string>
#include <memory>

#include "helpers/argumentnull_error.h"

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
    /// Represents the Body decorator, which wraps the rendered element in
    /// "<body>""</body>" tags.  This decorator is typically applied last.
    /// </summary>
    class BodyDecorator : public Decorator
    {
    public:

        /// <summary>
        /// Constructor that wraps the specified element.
        /// </summary>
        /// <param name="element">The IRenderElement to be decorated.
        /// Cannot be null.</param>
        /// <exception cref="argumentnull_error">The element being decorated
        /// cannot be null.</exception>
        BodyDecorator(IRenderElement::shared_ptr_t element)
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
            return std::format("<body>{0}</body>", Decorator::Render());
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Paragraph decorator, which wraps the rendered element in
    /// "<p>""</p>" tags.  This decorator is typically applied before the Body
    /// decorator.
    /// </summary>
    class ParagraphDecorator : public Decorator
    {
    public:

        /// <summary>
        /// Constructor that wraps the specified element.
        /// </summary>
        /// <param name="element">The IRenderElement to be decorated.
        /// Cannot be null.</param>
        /// <exception cref="argumentnull_error">The element being decorated
        /// cannot be null.</exception>
        ParagraphDecorator(IRenderElement::shared_ptr_t element)
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
            return std::format("<p>{0}</p>", Decorator::Render());
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Emphasis decorator, which wraps the rendered element in
    /// "<em>""</em>" tags.  This decorator is typically applied before any
    /// other decorator.
    /// </summary>
    class EmphasisDecorator : public Decorator
    {
    public:

        /// <summary>
        /// Constructor that wraps the specified element.
        /// </summary>
        /// <param name="element">The IRenderElement to be decorated.
        /// Cannot be null.</param>
        /// <exception cref="argumentnull_error">The element being decorated
        /// cannot be null.</exception>
        EmphasisDecorator(IRenderElement::shared_ptr_t element)
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
            return std::format("<em>{0}</em>", Decorator::Render());
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
