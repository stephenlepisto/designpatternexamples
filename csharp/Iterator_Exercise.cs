/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Iterator_Exercise "Iterator_Exercise"
/// class used in the @ref iterator_pattern.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref iterator_pattern in C#.
    /// 
    /// A custom container is instantiated (it already contains harcoded data
    /// to iterate over).  The custom container can then deliver three
    /// iterators, each providing a different aspect of the hardcoded data.
    /// 
    /// The output shows the output from each iterator.
    /// </summary>
    internal class Iterator_Exercise
    {
        /// <summary>
        /// Executes the example for the @ref iterator_pattern in C#.
        /// </summary>
        // ! [Using Iterator in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Iterator Exercise");

            // For this example, the class already has built into it the data
            // to be iterated over.
            IteratorContainer_Class items = new IteratorContainer_Class();

            Console.WriteLine("  Iterating over keys only:");
            var keyIterator = items.GetKeys();
            for (string item = keyIterator.Next(); item != null; item = keyIterator.Next())
            {
                Console.WriteLine("    {0}", item);
            }

            Console.WriteLine("  Iterating over values only:");
            var valueIterator = items.GetValues();
            for (string item = valueIterator.Next(); item != null; item = valueIterator.Next())
            {
                Console.WriteLine("    {0}", item);
            }

            Console.WriteLine("  Iterating over all items:");
            var itemIterator = items.GetItems();
            for (ItemPair item = itemIterator.Next(); item != null; item = itemIterator.Next())
            {
                Console.WriteLine("    {0} = {1}", item.Key, item.Value);
            }

            Console.WriteLine("  Done.");
        }
        // ! [Using Iterator in C#]
    }
}
