## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.iterator.iterator_exercise.Iterator_Exercise "Iterator_Exercise"()
#  function as used in the @ref iterator_pattern.

from .iterator_class import IteratorContainer_Class

##  Example of using the @ref iterator_pattern.
#  
#  A custom container is instantiated (it already contains hard-coded data
#  to iterate over).  The custom container can then deliver three
#  iterators, each providing a different aspect of the hard-coded data.
#  
#  The output shows the output from each iterator.

# ! [Using Iterator in Python]
def Iterator_Exercise():
    print()
    print("Iterator Exercise")

    # For this example, the class already has built into it the data
    # to be iterated over.
    items = IteratorContainer_Class()

    print("  Iterating over keys only:")
    keyIterator = items.GetKeys()
    item = keyIterator.Next()
    while item:
        print("    {0}".format(item))
        item = keyIterator.Next()

    print("  Iterating over values only:")
    valueIterator = items.GetValues()
    value = valueIterator.Next()
    while value:
        print("    {0}".format(value))
        value = valueIterator.Next()

    print("  Iterating over all items:")
    itemIterator = items.GetItems()
    key_value_pair = itemIterator.Next()
    while key_value_pair:
        print("    {0} = {1}".format(key_value_pair.Key, key_value_pair.Value))
        key_value_pair = itemIterator.Next()

    print("  Done.")
# ! [Using Iterator in Python]
