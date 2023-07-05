# Factory Pattern{#factory_pattern}

The Factory Method is also known as a Class factory and factory function.  Each
of these create instances of a class or structure.  There are two broad
categories of class factories:

1. Creates an instance of the same class each time it is called
2. Creates an instance of a class based on an argument passed to the factory

Both categories can also be set up to support the @ref singleton_pattern, just
by caching the first instance of whatever is being created and the returning
the cached instance on subsequent calls to the factory.

A class factory can be a function or a method on a class.  In the case of a
method on a class, first instantiate the class then call a method on the
instantiation to create an instance of another class or structure.  There are
many variations on a theme with class factories.

Class factories are typically used to instantiate a class but return the
instance represented by an interface.  In this way, the details of how the
core class is created is hidden away and the rest of the program only has an
interface to work with, thus creating good de-coupling and encapsulation of
functionality.

## Same Class Function

Here is a simple example of a class factory function in C++ that returns a new
instance of a class every time it is called:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}

struct IMyInterface
{
    virtual ~IMyInterface() { }

    void DoSomeWork() = 0;
};

namespace // Anonymous
{
    // This class is hidden from all other modules.  Use the CreateMyClass()
    // factory to instantiate this class.
    class MyClass : public IMyInterface
    {
    public:
        MyClass(int arg1, int arg2) { }
        ~MyClass() { }

        void DoSomeWork() override
        {
            // Do some work here
        }
    };
}

IMyInterface* CreateMyClass(int arg1, int arg2)
{
    return new MyClass(arg1, arg2); // MyClass implements IMyInterface
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note that arguments for the class to use can be passed to the class factory
function; these are passed on to the class constructor.  The rest of the
program has no idea how the IMyInterface is implemented and no access to the
internals of the MyClass class.  An instance of the IMyInterface is available
only through the class factory.

## Multiple Classes Function

A class function that can return instances of more than one class is basically
a variation on the same class function shown above.  However, all the classes
must implement the same interface.  An argument is passed to the class factory
function to specify which class to instantiate.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}

struct IMyInterface
{
    virtual ~IMyInterface() { }

    void DoSomeWork() = 0;
};

enum WhichClass
{
    Class1,
    Class2,
};

namespace // Anonymous
{
    // These classes are hidden from all other modules.  Use the CreateClass()
    // factory to instantiate these classes.

    class Class1 : public IMyInterface
    {
    public:
        Class1(int arg1, int arg2) { }
        ~Class1() { }

        void DoSomeWork() override
        {
            // Do some work here
        }
    };

    class Class2 : public IMyInterface
    {
    public:
        Class2(int arg1, int arg2) { }
        ~Class2() { }

        void DoSomeWork() override
        {
            // Do some work here
        }
    };
}

IMyInterface* CreateClass(WhichClass whichClass, int arg1, int arg2)
{
    switch (whichClass)
    {
       case WhichClass::Class1:
           return Class1(arg1, arg2);

        case WhichClass::Class2:
            return Class2(arg1, arg2);
    }
    return nullptr; // Indicate an unknown class option was selected
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## See Also

See the @ref singleton_pattern page for class factories that provide a singleton
instance of one class.

Here are additional examples of the factory pattern in action:

__C__

- SortStrategy_Initialize()
- CreateLogger()

__C++__

- DesignPatternExamples_cpp::Strategy_SortEntries_ClassFactory::Create()
- DesignPatternExamples_cpp::Logger::Logger()
    - A constructor that acts like a class factory but the instance is kept
      inside the Logger class, hidden from view.

__C#__

- DesignPatternExamples_csharp.Strategy_SortEntries_ClassFactory.Create()
- DesignPatternExamples_csharp.Logger.Logger()
    - A constructor that acts like a class factory but the instance is kept
      inside the Logger class, hidden from view.

__Python__

- DesignPatternExamples_python.strategy.strategy_sortentries_class.Strategy_SortEntries_ClassFactory.Create()
- DesignPatternExamples_python.bridge.bridge_logger.Logger class
    - A constructor that acts like a class factory but the instance is kept
      inside the Logger class, hidden from view.

### See Also
- @ref mainpage "Main page"
