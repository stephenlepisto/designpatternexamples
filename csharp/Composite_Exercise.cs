/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Composite_Exercise "Composite_Exercise"
/// class used in the @ref composite_pattern.

using System;
using System.Text;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref composite_pattern in C#.
    /// 
    /// The Composite pattern is used when a collection of objects is to
    /// be formed in a hierarchical form where each object needs to be
    /// treated like any other object but some objects can contain other
    /// objects.
    /// 
    /// This example uses a file structure of file and directories to
    /// represent each object type.
    /// </summary>
    internal class Composite_Exercise
    {

        /// <summary>
        /// Format the specified entry for display.
        /// 
        /// This is a recursive call.
        /// </summary>
        /// <param name="entry">The FileDirEntry object to format</param>
        /// <param name="depth">The current recursion depth.  This is used as
        /// leading space.</param>
        /// <returns>A string containing the formatted text for the given entry.</returns>
        string Composite_Exercise_FormatEntry(FileDirEntry entry, int depth)
        {
            const int NAME_PADDING_SIZE = 20;
            StringBuilder output = new StringBuilder();
            string spaces = new string(' ', depth * 2);
            output.AppendFormat("{0}{1}", spaces, entry.Name);
            int padding = NAME_PADDING_SIZE - entry.Name.Length - (depth * 2);
            if (entry.FileDirType == FileDirTypes.Directory)
            {
                output.Append("/");
                padding--;
            }
            output.AppendFormat("{0}", new string(' ', padding));
            output.AppendFormat("{0,4}", entry.Length);
            output.AppendFormat("  {0}", entry.WhenModified.ToString());
            output.AppendFormat("{0}", Environment.NewLine);

            FileDirEntry[] children = entry.Children;
            if (children != null)
            {
                for (int index = 0; index < children.Length; ++index)
                {
                    output.AppendFormat(Composite_Exercise_FormatEntry(children[index], depth + 1));
                }
            }

            return output.ToString();
        }


        /// <summary>
        /// Recursively display the contents of the hierarchical list of objects
        /// starting with the given object.
        /// </summary>
        /// <param name="entry"></param>
        void Composite_Exercise_ShowEntry(FileDirEntry entry)
        {
            string output = Composite_Exercise_FormatEntry(entry, 2);
            Console.WriteLine(output);
        }


        /// <summary>
        /// Executes the example for the @ref composite_pattern in C#.
        /// </summary>
        // ! [Using Composite in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Composite Exercise");
            try
            {
                string filepath = "root";
                FileDirEntry rootEntry = Composite_FileAccess.GetEntry(filepath);
                Console.WriteLine("  Showing object '{0}'", filepath);
                Composite_Exercise_ShowEntry(rootEntry);

                filepath = "root/subdir1/FileD.txt";
                rootEntry = Composite_FileAccess.GetEntry(filepath);
                Console.WriteLine("  Showing object '{0}'", filepath);
                Composite_Exercise_ShowEntry(rootEntry);
            }
            catch (System.IO.FileNotFoundException e)
            {
                Console.WriteLine("{0}: {1}", e.GetType().Name, e.Message);
            }
            Console.WriteLine("  Done.");
        }
        // ! [Using Composite in C#]
    }
}
