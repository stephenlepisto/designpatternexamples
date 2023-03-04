/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.IRenderElement "IRenderElement" interface,
/// the @ref DesignPatternExamples_csharp.Decorator "Decorator" base class,
/// @ref DesignPatternExamples_csharp.TextElement "TextElement" class, and the
/// concrete decorator classes used in the @ref decorator_pattern "Decorator pattern".

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
