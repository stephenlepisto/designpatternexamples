// Decorator design pattern example.
//
// The decorator pattern provides a way to extend capabilities to an instance
// of a class without altering the original class.  The intention is to extend
// the capabilities at runtime, providing a dynamic and potentially user-driven
// level of extension.  This is done by having the decorators provide the same
// interface as the object being decorated.  that way, the decorators can wrap
// the object or other decorators and still look like the same kind of object
// to the calling entity.
//
// This kind of architecture requires cooperation among all the decorators and
// classes being decorated by having each class implement the same abstract
// interface (again, so all the classes look the same to each other).  The
// decorators then wrap any object with the same abstract interface.  The 
// ability of decorators being able to wrap other decorators automatically
// builds a kind of nested hierarchy, similar to a Composite pattern except
// that the decorators don't typically support multiple children in a single
// decorator.
//
// Since each decorator looks like any other decorator (of the same kind),
// the decorators need to be designed to work in pretty much any order,
// with the core class taking whatever parameters it needs to (by definition,
// the core class does not take a decorator; decorators are applied to the
// core class by wrapping the core class).
//
// In this example, the core class is called TextElement and up to three
// decorators can be applied (BodyElement, ParagraphElement, and
// EmphasisElement).  Decorators should ideally be designed to be applied
// in any order but as this example shows, there is often a specific order
// for the decorators to be used.  This order is specified in the
// documentation.  All decorators and the TextElement class implement the
// IRenderElement interface.
//
// Frequently the decorator pattern is combined with the Composite pattern
// so that wrapped elements can contain child elements that are each wrapped
// by one or more decorators (basically, the classes that participate in the
// Composite pattern also support decorators).

using System;
using System.Xml.Linq;

namespace DesignPatternExamples_csharp
{

    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents an element that can be rendered in text.  All decorators
    /// and the core element class implement this interface.
    /// </summary>
    public interface IRenderElement
    {
        /// <summary>
        /// Render this element as a string.
        /// </summary>
        /// <returns>A string containing the rendering of the element.</returns>
        string Render();
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the base class of all decorators and is responsible for
    /// handling the wrapped element being decorated.
    /// </summary>
    public class Decorator : IRenderElement
    {
        IRenderElement _wrappedElement;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="wrappedElement">The IRenderElement element to be
        /// wrapped.</param>
        /// <exception cref="ArgumentNullException">The element being decorated
        /// cannot be null.</exception>
        public Decorator(IRenderElement wrappedElement)
        {
            if (wrappedElement == null)
            {
                throw new ArgumentNullException("wrappedElement",
                    "The element being decorated cannot be null.");
            }
            _wrappedElement = wrappedElement;
        }

        /// <summary>
        /// Retrieves the rendering of the wrapped element.
        /// </summary>
        /// <returns>A string containing the rendered wrapped element.</returns>
        virtual public string Render()
        {
            return _wrappedElement.Render();
        }
    }

    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the WhiteBackground decorator, which changes the background
    /// color of the wrapped element to white.
    /// </summary>
    public class WhiteBackgroundDecorator : Decorator
    {
        /// <summary>
        /// Constructor that wraps the specified element.
        /// </summary>
        /// <param name="element">The IRenderElement to be decorated.
        /// Cannot be null.</param>
        /// <exception cref="ArgumentNullException">The element being decorated
        /// cannot be null.</exception>
        public WhiteBackgroundDecorator(IRenderElement element) : base(element)
        {
        }

        /// <summary>
        /// Render the wrapped element with decorations.
        /// </summary>
        /// <returns>A string containing the decorated rendered element.</returns>
        public override string Render()
        {
            return String.Format("\x1b[47m{0}\x1b[49m", base.Render());
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Underline decorator, which underlines the wrapped
    /// content.
    /// </summary>
    public class UnderlineDecorator : Decorator
    {
        /// <summary>
        /// Constructor that wraps the specified element.
        /// </summary>
        /// <param name="element">The IRenderElement to be decorated.
        /// Cannot be null.</param>
        /// <exception cref="ArgumentNullException">The element being decorated
        /// cannot be null.</exception>
        public UnderlineDecorator(IRenderElement element) : base(element)
        {
        }


        /// <summary>
        /// Render the wrapped element with decorations.
        /// </summary>
        /// <returns>A string containing the decorated rendered element.</returns>
        override public string Render()
        {
            return String.Format("\x1b[4m{0}\x1b[24m", base.Render());
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the RedForeground decorator, which renders the wrapped
    /// content as red text.
    /// </summary>
    public class RedForegroundDecorator : Decorator
    {
        /// <summary>
        /// Constructor that wraps the specified element.
        /// </summary>
        /// <param name="element">The IRenderElement to be decorated.
        /// Cannot be null.</param>
        /// <exception cref="ArgumentNullException">The element being decorated
        /// cannot be null.</exception>
        public RedForegroundDecorator(IRenderElement element) : base(element)
        {
        }


        /// <summary>
        /// Render the wrapped element with decorations.
        /// </summary>
        /// <returns>A string containing the decorated rendered element.</returns>
        override public string Render()
        {
            return String.Format("\x1b[31m{0}\x1b[39m", base.Render());
        }
    }


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
    public class TextElement : IRenderElement
    {
        string _elementText;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="element">The text to be rendered.</param>
        public TextElement(string element)
        {
            _elementText = element;
        }

        #region IRenderElement Members

        /// <summary>
        /// Render this element as a string.
        /// </summary>
        /// <returns>A string containing the rendering of the element.</returns>
        public string Render()
        {
            return _elementText;
        }

        #endregion
    }
}
