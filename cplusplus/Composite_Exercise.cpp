
/// @file
/// @brief
/// Implementation of the Composite_Exercise() function as used in the 
/// @ref composite_pattern.

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <filesystem>
#include <iostream>

#include "Composite_Exercise.h"
#include "Composite_FileDirEntry.h"
#include "Composite_FileAccess.h"


namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;

    /// <summary>
    /// Format the specified entry for display.
    /// 
    /// This is a recursive call.
    /// </summary>
    /// <param name="entry">The FileDirEntry object to format</param>
    /// <param name="depth">The current recursion depth.  This is used as
    /// leading space.</param>
    /// <returns>A string containing the formatted text for the given entry.</returns>
    std::string Composite_Exercise_FormatEntry(FileDirEntry* entry, int depth)
    {
        const size_t NAME_PADDING_SIZE = 20;
        std::string output = "";
        std::string spaces(static_cast<size_t>(depth) * 2, ' ');
        output.append(std::format("{0}{1}", spaces, entry->Name()));
        size_t padding = NAME_PADDING_SIZE - entry->Name().size() - (static_cast<size_t>(depth) * 2);
        if (entry->FileDirType() == FileDirTypes::Directory)
        {
            output.append("/");
            padding--;
        }
        output.append(std::string(padding, ' '));
        output.append(std::format("{0:4}", entry->Length()));
        output.append(std::format("  {0}", entry->WhenModified().ToString()));
        output.append("\n");

        FileDirEntryList children = entry->Children();
        if (!children.empty())
        {
            for (int index = 0; index < children.size(); ++index)
            {
                output.append(Composite_Exercise_FormatEntry(children[index].get(), depth + 1));
            }
        }

        return output;
    }


    /// <summary>
    /// Recursively display the contents of the hierarchical list of objects
    /// starting with the given object.
    /// </summary>
    /// <param name="entry">The file entry to display</param>
    void Composite_Exercise_ShowEntry(FileDirEntry* entry)
    {
        std::string output = Composite_Exercise_FormatEntry(entry, 2);
        std::cout << output << std::endl;
    }

} // end namespace anonymous


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref composite_pattern "Composite" design pattern.
    /// 
    /// The Composite pattern is used when a collection of objects is to
    /// be formed in a hierarchical form where each object needs to be
    /// treated like any other object but some objects can contain other
    /// objects.
    /// 
    /// This example uses a file structure of file and directories to
    /// represent each object type.
    /// </summary>
    // ! [Using Composite in C++]
    void Composite_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Composite Exercise" << std::endl;

        try
        {
            std::string filepath = "root";
            FileDirEntry* rootEntry = Composite_FileAccess::GetEntry(filepath);
            std::cout << "  Showing object '" << filepath << "'" << std::endl;
            Composite_Exercise_ShowEntry(rootEntry);

            filepath = "root/subdir1/FileD.txt";
            rootEntry = Composite_FileAccess::GetEntry(filepath);
            std::cout << "  Showing object '" << filepath << "'" << std::endl;
            Composite_Exercise_ShowEntry(rootEntry);
        }
        catch (std::filesystem::filesystem_error& e)
        {
            std::cout << "Error! filesystem_error: " << e.what() << std::endl;
        }

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Composite in C++]

} // end namespace
