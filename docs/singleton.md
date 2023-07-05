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
creating an entire example to demonstrate it seems pointless.  The 
@ref facade_pattern has a good example of the singleton pattern in action, in
several programming language so see the links below for those.  However, the
above example demonstrates everything needed.

## See Also

__C++__

- DesignPatternExamples_cpp::CreateLowLevelInstance()
- DesignPatternExamples_cpp::CreateHighLevelInstance()

__C#__

- DesignPatternExamples_csharp.Facade_ComplicatedSubSystemFactory.CreateLowLevelInstance()
- DesignPatternExamples_csharp.Facade_ComplicatedSubSystemFactory.CreateHighLevelInstance()

__Python__

- DesignPatternExamples_python.facade.facade_complicatedsubsystem.CreateLowLevelInstance()
- DesignPatternExamples_python.facade.facade_highlevelsystem.CreateHighLevelInstance()


### See Also
- @ref mainpage "Main page"
