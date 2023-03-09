/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Strategy_SortEntries_ClassFactory "Strategy_SortEntries_ClassFactory"
/// class as used in the @ref strategy_pattern "Strategy pattern".

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
            optionAsString = std::format("Unknown {0}", static_cast<int>(sortOption));
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
            std::string message = std::format("Unrecognized sort option: {0}", _SortOptionToString(sortOption));
            throw std::runtime_error(message.c_str());
        }
        }

        return sortEntries;
    }

} // end namespace
