/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Strategy_SortEntries_ClassFactory "Strategy_SortEntries_ClassFactory"
/// class as used in the @ref strategy_pattern.

#include <stdexcept>

#include "helpers/formatstring.h"

#include "Strategy_SortEntries_Classes.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;

    /// <summary>
    /// Convert a SortOptions enumeration to a string.
    /// </summary>
    /// <param name="sortOption">A value from the SortOptions enumeration.</param>
    /// <returns>A string representation of the value.</returns>
    std::string _SortOptionToString(SortOptions sortOption)
    {
        std::string optionAsString;

        switch (sortOption)
        {
        case SortOptions::ByName:
            optionAsString = "ByName";
            break;

        case SortOptions::ByAge:
            optionAsString = "ByAge";
            break;

        case SortOptions::ByHeight:
            optionAsString = "ByHeight";
            break;

        default:
            optionAsString = Helpers::formatstring("Unknown %d", static_cast<int>(sortOption));
            break;
        }
        return optionAsString;
    }


} // end anonymous namespace


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


namespace DesignPatternExamples_cpp
{

    ISortEntries::shared_ptr_t Strategy_SortEntries_ClassFactory::Create(SortOptions sortOption, bool reversedSort)
    {
        ISortEntries::shared_ptr_t sortEntries;

        switch (sortOption)
        {
        case SortOptions::ByName:
            sortEntries = std::make_shared<Strategy_SortEntries_ByName>(reversedSort);
            break;

        case SortOptions::ByAge:
            sortEntries = std::make_shared < Strategy_SortEntries_ByAge>(reversedSort);
            break;

        case SortOptions::ByHeight:
            sortEntries = std::make_shared < Strategy_SortEntries_ByHeight>(reversedSort);
            break;

        default:
        {
            std::string message = Helpers::formatstring("Unrecognized sort option: %s", _SortOptionToString(sortOption).c_str());
            throw std::runtime_error(message.c_str());
        }
        }

        return sortEntries;
    }

} // end namespace
