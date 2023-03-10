
/// @file
/// @brief
/// Implementation of the Iterator_Exercise() function as used in the 
/// @ref iterator_pattern "Iterator pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "Iterator_Exercise.h"
#include "Iterator_Class.h"


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref iterator_pattern "Iterator" design pattern.
    /// 
    /// A custom container is instantiated (it already contains hard-coded data
    /// to iterate over).  The custom container can then deliver three
    /// iterators, each providing a different aspect of the hard-coded data.
    /// 
    /// The output shows the output from each iterator.
    /// </summary>
    //! [Using Iterator in C++]
    void Iterator_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Iterator Exercise" << std::endl;

        // For this example, the class already has built into it the data
        // to be iterated over.
        IteratorContainer_Class items;

        std::cout << "  Iterating over keys only:" << std::endl;
        auto keyIterator = items.GetKeys();
        std::string item;
        while (keyIterator->Next(item))
        {
            std::cout << std::format("    {0}", item) << std::endl;
        }

        std::cout << "  Iterating over values only:" << std::endl;
        auto valueIterator = items.GetValues();
        std::string value;
        while (valueIterator->Next(value))
        {
            std::cout << std::format("    {0}", value) << std::endl;
        }

        std::cout << "  Iterating over all items:" << std::endl;
        auto itemIterator = items.GetItems();
        ItemPair key_value_pair;
        while (itemIterator->Next(key_value_pair))
        {
            std::cout << std::format("    {0} = {1}", key_value_pair.Key, key_value_pair.Value) << std::endl;
        }

        std::cout << "  Done." << std::endl;
    }
    //! [Using Iterator in C++]

} // end namespace
