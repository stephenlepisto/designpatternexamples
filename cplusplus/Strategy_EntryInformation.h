/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::EntryInformation "EntryInformation"
/// class as used for data in the @ref strategy_pattern.

#pragma once
#ifndef __STRATEGY_ENTRYINFORMATION_H__
#define __STRATEGY_ENTRYINFORMATION_H__

#include <memory>
#include <string>

#include "helpers/formatstring.h"

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
            return Helpers::formatstring("%6s %3d %3d\"", Name.c_str(), Age, Height);
        }
    };

} // end namespace

#endif // __STRATEGY_ENTRYINFORMATION_H__

