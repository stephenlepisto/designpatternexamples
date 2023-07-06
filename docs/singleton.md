# Singleton Pattern{#singleton_pattern}

The singleton pattern is intended to ensure that only one instance of a class
or structure is created, and that subsequent requests for an instance of that
class or structure returns the first instance created.

The singleton is typically accomplished through a global static variable that
is managed through a function or method.  On the first call, the function
determines if the global variable has been set and it not, creates an instance
of the appropriate class or structure and stores it in the global variable.
The function then returns the contents of the global variable.

As an example, a singleton function looks like this in C++:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
static std::unique_ptr<MyClass> _instance;

MyClass* CreateLowLevelInstance()
{
    if (!_instance)
    {
        _instance = std::make_uinique<MyClass>();
    }
    return _instance.get();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A smart pointer is used so the object is deleted when the program exits.

As can be seen in the above example, the singleton pattern is somewhat
dependent on the features of the programming language being used and is
primarily for object-oriented code.  However, the pattern is so simple that
creating an entire example to demonstrate it seems pointless.

## How to Use

The above example demonstrates everything needed to implement the basic factory
pattern.  For a more detailed example of the singleton pattern, see the
following links into the @ref facade_pattern examples for several languages.

__C__

- Proxy_GetRealService()

__C++__

- DesignPatternExamples_cpp::CreateLowLevelInstance()
- DesignPatternExamples_cpp::CreateHighLevelInstance()
- Proxy_Class_Private::Proxy_Class::_GetRealClass()

__C#__

- DesignPatternExamples_csharp.Facade_ComplicatedSubSystemFactory.CreateLowLevelInstance()
- DesignPatternExamples_csharp.Facade_ComplicatedSubSystemFactory.CreateHighLevelInstance()
- DesignPatternExamples_csharp.Proxy_Classes_Container.Proxy_Class._GetRealClass()

__Python__

- DesignPatternExamples_python.facade.facade_complicatedsubsystem.CreateLowLevelInstance()
- DesignPatternExamples_python.facade.facade_highlevelsystem.CreateHighLevelInstance()
- DesignPatternExamples_python.proxy.proxy_class.Proxy_Class._GetRealClass()


### See Also
- @ref mainpage "Main page"
