/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Visitor_Exercise "Visitor_Exercise"
/// class used in the @ref visitor_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref visitor_pattern in C#.
    /// 
    /// The Visitor pattern is used to add functionality to a list of
    /// otherwise unchanging element objects by passing a visitor object to
    /// each element object.  Each element object calls the visitor object,
    /// passing itself as an argument.  The visitor object then does
    /// something based on the type of the element.
    /// 
    /// In this exercise, a collection of shop objects is initialized then
    /// an order visitor is created to retrieve an item from one of the shop
    /// objects.  Along the way, shops that don't have the necessary
    /// ingredients use another order visitor to order ingredients from
    /// other shops.  This approach assumes no two shops sell the same
    /// thing.
    /// </summary>
    internal class Visitor_Exercise
    {
        /// <summary>
        /// Executes the example for the @ref visitor_pattern in C#.
        /// </summary>
        // ! [Using Visitor in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Visitor Exercise");

            Console.WriteLine("  Creating Village");
            Village village = new Village();
            village.LoadVillage();

            OrderVisitor visitor = new OrderVisitor(new string[] { "hamburger" });
            Console.WriteLine("  Ordering a hamburger from a shop in the {0}", village.Name);
            // Visit all shops and place an order for a hamburger at the shop
            // that sells them.  We don't know which shop it is and we don't
            // need to know until we receive the order.
            village.Accept(visitor);
            if (visitor.ItemsReceived.Count > 0)
            {
                // We are expecting only a single item
                Console.WriteLine("  We received a {0} from {1}.",
                    visitor.ItemsReceived[0], visitor.ShopNameReceivedFrom);
            }
            else
            {
                Console.WriteLine("  Failed to receive a hamburger");
            }

            Console.WriteLine("  Done.");
        }
        // ! [Using Visitor in C#]

    }
}
