/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::EntryInformation "EntryInformation"
/// class as used for data in the @ref strategy_pattern.

#pragma once
#ifndef __STRATEGY_ENTRYINFORMATION_H__
#define __STRATEGY_ENTRYINFORMATION_H__

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <memory>
#include <string>

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents an individual with a Name, Age, and Height.
    /// </summary>
    struct EntryInformation
    {
        /// <summary>
        /// Alias to make it easier to work with a shared pointer.
        /// </summary>
        using shared_ptr_t = std::shared_ptr<EntryInformation>;

        /// <summary>
        /// Name of this individual.
        /// </summary>
        std::string Name;

        /// <summary>
        /// Age of this individual, in years.
        /// </summary>
        int Age;

        /// <summary>
        /// Height of this individual, in inches.
        /// </summary>
        int Height;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name of the individual.</param>
        /// <param name="age">Age of the individual (in years).</param>
        /// <param name="height">Height of the individual (in inches).</param>
        EntryInformation(std::string name, int age, int height)
            : Name(name)
            , Age(age)
            , Height(height)
        {
        }


        /// <summary>
        /// Convert the entry into a string.  In this case, a formatted
        /// string where name, age, and height are confined to columns.
        /// </summary>
        /// <returns></returns>
        std::string ToString()
        {
            return std::format("{0:6} {1:3} {2:3}\"", Name, Age, Height);
        }
    };

} // end namespace

#endif // __STRATEGY_ENTRYINFORMATION_H__

