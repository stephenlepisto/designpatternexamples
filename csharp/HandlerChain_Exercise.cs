/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.HandlerChain_Exercise "HandlerChain_Exercise"
/// class used in the @ref handlerchain_pattern.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref handlerchain_pattern or Chain of Responsibility
    /// pattern in C#.
    /// 
    /// The Handler Chain pattern is used to support a dynamic list of
    /// handlers that are passed the same arguments.  It is kind of the
    /// inverse of the Visitor pattern, where the Visitor pattern is a
    /// handler that is passed to all objects in a list and the Handler
    /// Chain pattern is an object passed to handlers in a list.
    ///
    /// In this exercise, multiple rectangular regions called
    /// MessageWindows embody the handlers and the HandlerChain object
    /// passes message objects to each MessageWindow until the message is
    /// handled.
    /// </summary>
    internal class HandlerChain_Exercise
    {
        /// <summary>
        /// Helper method to construct a list of windows.  Messages will be passed 
        /// to these windows via the HandlerChain object.
        /// </summary>
        /// <param name="handlerChain">The HandlerChain object that receives the
        /// new windows.</param>
        void _HandlerChain_ConstructWindowChain(HandlerChain handlerChain)
        {
            // Note: This creates each window and adds the new window to the given
            // HandlerChain object.
            //
            // This example doesn't care about each individual window so the
            // return value is ignored.
            MessageWindow.CreateWindow("Window 1", 0, 0, 10, 10, handlerChain);
            MessageWindow.CreateWindow("Window 2", 20, 0, 5, 5, handlerChain);
            MessageWindow.CreateWindow("Window 3", 30, 10, 15, 15, handlerChain);
        }

        /// <summary>
        /// Executes the example for the @ref handlerchain_pattern in C#.
        /// </summary>
        // ! [Using HandlerChain in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Handler Chain Exercise");

            // Construct a handler chain and populate with windows that can
            // handle messages.
            HandlerChain handlerChain = new HandlerChain();
            _HandlerChain_ConstructWindowChain(handlerChain);

            Console.WriteLine("  Handler Chain at start:");
            Console.WriteLine(handlerChain);

            // Now pass messages to the windows.

            Console.WriteLine("  Select Window 2");
            handlerChain.SendMessage(new Message(MessageType.ButtonDown, new MessagePosition(22, 1)));
            handlerChain.SendMessage(new Message(MessageType.ButtonUp, new MessagePosition(22, 1)));
            Console.WriteLine("  Current handler chain:");
            Console.WriteLine(handlerChain);

            Console.WriteLine("  Select Window 3");
            handlerChain.SendMessage(new Message(MessageType.ButtonDown, new MessagePosition(35, 11)));
            handlerChain.SendMessage(new Message(MessageType.ButtonUp, new MessagePosition(35, 11)));
            Console.WriteLine("  Current handler chain:");
            Console.WriteLine(handlerChain);

            Console.WriteLine("  Select Window 1");
            handlerChain.SendMessage(new Message(MessageType.ButtonDown, new MessagePosition(4, 4)));
            handlerChain.SendMessage(new Message(MessageType.ButtonUp, new MessagePosition(4, 4)));
            Console.WriteLine("  Current handler chain:");
            Console.WriteLine(handlerChain);

            Console.WriteLine("  Close Window 2");
            handlerChain.SendMessage(new Message(MessageType.ButtonDown, new MessagePosition(24, 0)));
            handlerChain.SendMessage(new Message(MessageType.ButtonUp, new MessagePosition(24, 0)));
            Console.WriteLine("  Current handler chain:");
            Console.WriteLine(handlerChain);

            Console.WriteLine("  Done.");
        }
        // ! [Using HandlerChain in C#]
    }
}
