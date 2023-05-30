/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Decorator_Exercise "Decorator_Exercise"
/// class used in the @ref decorator_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref decorator_pattern in C#.
    /// 
    /// The Decorator pattern is used when a class instance at run time needs
    /// to have its behavior altered.  This is supported by providing wrapper
    /// classes called decorators that take instances of the IRenderElement
    /// interface.  All elements look the same and can therefore recursively
    /// wrap other decorators.  The base element never wraps anything and
    /// decorators must ultimately wrap a non-decorator class to be of any
    /// use.
    /// </summary>
    internal class Decorator_Exercise
    {
        /// <summary>
        /// Executes the example for the @ref decorator_pattern in C#.
        /// </summary>
        // ! [Using Decorator in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Decorator Exercise");
            IRenderElement baseElement = new TextElement("This is raw text");

            // Wrap the base element in three decorators.
            IRenderElement wrappedElement =
                new WhiteBackgroundDecorator(
                    new UnderlineDecorator(
                        new RedForegroundDecorator(baseElement)));

            // Now render the elements to the console.
            Console.WriteLine("  base Text element: \"{0}\"", baseElement.Render());
            Console.WriteLine("  Decorated element: \"{0}\"", wrappedElement.Render());
            Console.WriteLine("  Done.");
        }
        // ! [Using Decorator in C#]
    }
}
