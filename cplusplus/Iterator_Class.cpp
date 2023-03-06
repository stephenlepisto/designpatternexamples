/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::IteratorContainer_Class "IteratorContainer_Class"
/// class as used in the @ref iterator_pattern "Iterator pattern".
#include "Iterator_Class.h"

namespace // Anonymous
{
    // Hardcoded data to be iterated over.
    // The number of keys must match the number of values.

    std::string _keys[] = { std::string("One"), std::string("Two"), std::string("Three") };
    std::string _values[] = { std::string("Value 1"), std::string("Value 2"), std::string("Value 3") };

} // end anonymous namespace


namespace DesignPatternExamples_cpp
{

    std::shared_ptr<IIterator<ItemPair>> IteratorContainer_Class::GetItems()
    {
        std::vector<ItemPair> items;

        size_t numItems = _countof(_keys);
        for (size_t index = 0; index < numItems; ++index)
        {
            items.push_back(ItemPair(_keys[index], _values[index]));
        }

        return std::make_shared<Iterator<ItemPair>>(&items[0], items.size());
    }


    std::shared_ptr<IIterator<std::string>> IteratorContainer_Class::GetKeys()
    {
        return std::make_shared<Iterator<std::string>>(_keys, _countof(_keys));
    }


    std::shared_ptr < IIterator<std::string>> IteratorContainer_Class::GetValues()
    {
        return std::make_shared<Iterator<std::string>>(_values, _countof(_values));
    }

} // end namespace
