/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Proxy_Exercise "Proxy_Exercise"
/// class used in the @ref proxy_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref proxy_pattern in C#.
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
    internal class Proxy_Exercise
    {
        /// <summary>
        /// Executes the example for the @ref proxy_pattern in C#.
        /// </summary>
        // ! [Using Proxy in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Proxy Exercise");

            Console.WriteLine("  Getting proxy object...");
            IWorkByProxy proxyObject = Proxy_Classes_Container.CreateProxy();

            Console.WriteLine("  Calling Dowork() on proxy...");
            string output = proxyObject.DoWork("Initial call");
            Console.WriteLine("  Output from proxy = \"{0}\"", output);

            Console.WriteLine("  Calling Dowork() on proxy...");
            output = proxyObject.DoWork("Second call");
            Console.WriteLine("  Output from proxy = \"{0}\"", output);

            Console.WriteLine("  Calling Dowork() on proxy...");
            output = proxyObject.DoWork("Third call");
            Console.WriteLine("  Output from proxy = \"{0}\"", output);
            Console.WriteLine("  Done.");
        }
        // ! [Using Proxy in C#]
    }
}
