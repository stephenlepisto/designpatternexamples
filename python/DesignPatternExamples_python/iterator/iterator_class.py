## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.iterator.iterator_class.IteratorContainer_Class "IteratorContainer_Class"
#  class, the
#  @ref DesignPatternExamples_python.iterator.iterator_class.IIterator "IIterator"
#  interface, along with the implementations of the
#  @ref DesignPatternExamples_python.iterator.iterator_class.Iterator "Iterator"
#  and
#  @ref DesignPatternExamples_python.iterator.iterator_class.ItemPair "ItemPair"
#  classes as used in the @ref iterator_pattern.

from abc import ABC, abstractmethod
from typing import TypeVar, Generic, Sequence

## Represents a generic type for IIterator class
T = TypeVar('T')
## Represents a generic type for Iterator class
T2 = TypeVar('T2')

## Alias for Generic to be used in the Iterator class to dance around a problem
#  with Doxygen thinking there is a recursive relationship with IIterator class.
Generic2 = Generic

## Represents a key/value pair where the key and value are strings.
class ItemPair:

    ## Constructor
    #
    #  @param key
    #         The key to use.
    #  @param value
    #         The value to use.
    def __init__(self, key = "", value = "") -> None:
        self.Key = key
        self.Value = value

    ## @var Key
    #       The key used to match the item pair
    #  @var Value
    #       The value of the item pair


##############################################################################
##############################################################################


## Represents an iterator for some type.  This is a forward-only iterator
#  in that it can only start at 0 and increment through the items until
#  done.
#
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.py}
#  iterator = container.GetItems()
#  itempair = iterator.Next()
#  while itempair:
#      # Use item here
#      itempair = iterator.Next()
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  A generic type is used in this example to explore generic type hints in
#  Python.  Technically, this "generic type" is not needed as Python is already
#  pretty much generic through duck-typing.  However, I am using two different
#  types of IIterator (ItemPair and str), so I might as well make it explicit
#  that IIterator handles different types.
#
#  Note: The Generic[T] base class is inherited by the
#  @ref DesignPatternExamples_python.iterator.iterator_class.Iterator "Iterator"
#  class, and that goes for the T type as well.  So, unlike C++ or C#, the
#  class implementing the interface does not need to be explicitly declared to
#  have a generic type.
#
#  Also, in Python, these are type hints and do not affect how the program
#  executes, only how it reads.
class IIterator(ABC, Generic[T]):

    ## Start iteration from beginning of container.
    @abstractmethod
    def Reset(self) -> None:
        pass

    ## Retrieve the next item from the container.
    #
    #  @returns
    #      Returns a `T` object or null, if there are no more items in
    #      the iteration.
    def Next(self) -> T:
        pass


##############################################################################
##############################################################################


## Represents an iterator for a container by implementing the IIterator
#  interface.
#  
#  This class retains a copy of the elements to be iterated over so it is
#  immune to changes in the container from which this iterator was
#  generated.
#
#  This iterator is immune to changes in the source container.  However,
#  that makes this iterator expensive because the items being iterated
#  over have to be duplicated in this class.
#  
#  One alternative is for there to be only a single iterator and that
#  iterator is implemented on the container class itself.  If there are
#  more than one type of iterator (as in this example) then the source
#  container would have to implement multiple iterators, one for each
#  type of item returned from the iterator.
#  
#  Another alternative is for this iterator class to have a way to access
#  the source container's data so the data doesn't have to be copied.
class Iterator(IIterator, Generic2[T2]):

    ##  Constructor.
    #
    #  @param items
    #         The items to iterate over.
    #  @param numItems
    #         Number of items in the array.
    def __init__(self, items : Sequence[T2], numItems: int) -> None:
        self._items = items.copy()
        self._numItems = numItems
        self._index = 0

    ## @var _items
    #       The array of items to iterate over.
    #  @var _numItems
    #       The number of items in the array of items.
    #  @var _index
    #       The index into the _items array to the next item.

    ## Fetches the next item in the iteration, if any.
    #
    #  @returns
    #     Returns the next item in the iterator.  Returns None if there are no
    #     more items to return
    def Next(self) -> T2:
        retrieved_item = None
        if self._index < self._numItems:
            retrieved_item = self._items[self._index]
            self._index += 1
        return retrieved_item

    ## Reset the iterator to the beginning.
    def Reset(self) -> None:
        self._index = 0


##############################################################################
##############################################################################


## Represents a container that offers up two kinds of iterators for the
#  hardcoded contents, ItemPair and string.
#  
#  This container is not a dictionary despite the use of keys and values but
#  it was the simplest form of data I could come up with that only used the
#  simplest of the Python containers, a list.
class IteratorContainer_Class:
    # Hardcoded data to be iterated over.
    # The number of keys must match the number of values.

    ## Hardcoded keys associated with the hardcoded values in `_values`.
    _keys = [ "One", "Two", "Three" ]

    ## Hardcoded values associated with the harcoded keys in `_keys`.
    _values = [ "Value 1", "Value 2", "Value 3" ]

    ## Retrieve an iterator over the data that returns an
    #  @ref DesignPatternExamples_python.iterator.iterator_class.ItemPair "ItemPair"
    #  object containing both key and value for each entry.
    #
    #  @returns
    #     An
    #     @ref DesignPatternExamples_python.iterator.iterator_class.IIterator "IIterator"
    #     object for getting ItemPair objects.
    def GetItems(self) -> IIterator[ItemPair]:
        items = [] # type:list[ItemPair]

        numItems = len(IteratorContainer_Class._keys)
        for index in range(0, numItems):
            items.append(ItemPair(IteratorContainer_Class._keys[index],
                                  IteratorContainer_Class._values[index]))

        return Iterator[ItemPair](items, len(items))
        #return Iterator(items, len(items))

    ## Retrieve an iterator over the "key" part of the data, where the
    #  data returned from the iterator is a string type.
    #
    #  @returns
    #     An
    #     @ref DesignPatternExamples_python.iterator.iterator_class.IIterator "IIterator"
    #     object for getting strings.
    def GetKeys(self) -> IIterator[str]:
        return Iterator[str](IteratorContainer_Class._keys, len(IteratorContainer_Class._keys))

    ## Retrieve an iterator over the "value" part of the data, where the
    #  data returned from the iterator is a string type.
    #
    #  @returns
    #     An
    #     @ref DesignPatternExamples_python.iterator.iterator_class.IIterator "IIterator"
    #     object for getting strings.
    def GetValues(self) -> IIterator[str]:
        return Iterator[str](IteratorContainer_Class._values, len(IteratorContainer_Class._values))
