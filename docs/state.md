# State Pattern {#state_pattern}

@image html state_diagram.png "Diagram of the State pattern"

The State pattern is used when a finite state machine needs to be expressed
in an object-oriented form.

A finite state machine is something that changes its behavior based on its
state.  It is a way to isolate specific behaviors from each other so that
changes in one behavior doesn't affect other behaviors.  There is also a
performance benefit in that only a minimum amount of code is executed at
any given time for any given state.

Here is a simple state machine, written in C:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
/* Describes the current state of the state machine. */
enum CurrentState
{
    InitState,  /* Always transitions to State1 */
    State1,     /* Can transition to State1 or State2 */
    State2,     /* Can transition to State1 or EndState */
    EndState    /* Exit condition and transitions to InitState */
};

/*
   Execute one step of the state machine, returning 1 if more state
   needs to be executed; otherwise, returns 0 if processing is done
*/
int ProcessData(CurrentState* pState, void* pData)
{
    int continueProcessing = 1;

    switch (*pState):
    {
        case InitState:
            DoInitialize(pData);
            *pState = State1;
            break;

        case State1:
            *pState = DoState1();
            break;

        case State2:
            *pState = DoState2();
            break;

        case EndState:
            DoEndState();
            continueProcessing = 0;
            *pState = InitState;
            break;
    }
    return continueProcessing;
}

/* Execute the state machine on the given data, returning when done. */
void ExecuteStateMachine(void *pData)
{
    CurrentState state = InitState;
    while (ProcessData(&state, pData) != 0)
    {
    }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For the above example, the details of DoInitialize(), DoState1(), DoState2()
and DoEndState() don't matter except that DoState1() and DoState2() can
change the state depending on some internal decision-making process.
However, the overall flow should be clear that only one function is called
for any given state.

The State design pattern describes a way to convert the above functional
definition into an object-oriented one.

The CurrentState enumeration and the functions that do stuff for each state
are encapsulated into classes.  These state classes derive from a common
base class or interface.  The ProcessData() function is encapsulated in a
context class that is passed to each state class (so the state class can
operate on the data in the context).  The driving force (that is, whatever
makes the call to the state machine) is typically from outside the context
class and will tend to look a lot like the ExecuteStateMachine() function
in the above example, although the driving force could be anything from a
timer to the user clicking a button.

As the state changes in the context class, a pointer to the current state
class instance is changed to the next state class instance (as opposed to
changing a simple integer or enumeration).  There are two basic ways in
which the state is changed:

1. each state class knows what the next state class needs to be and
   returns an instance of that class
2. The context maintains a dictionary of the state class instances and
   uses an enumeration such as CurrentState to look up the next state
   instance to use.  Each state class then returns a value from the
   CurrentState to set the next state.

The second approach is better so that only one entity (the context class)
knows about the instances of the state classes.

# How to Use

Links to the State interface and class descriptions:
- @ref DesignPatternExamples_cpp::IStateContext "IStateContext" interface (C++)
- @ref DesignPatternExamples_csharp::IStateContext "IStateContext" interface (C#)
- @ref DesignPatternExamples_cpp::IStateBehavior "IStateBehavior" interface (implemented by state classes) (C++)
- @ref DesignPatternExamples_csharp::IStateBehavior "IStateBehavior" interface (implemented by state classes) (C#)
- @ref DesignPatternExamples_cpp::StateContext_Class "StateContext_Class" class (C++)
- @ref DesignPatternExamples_csharp.StateContext_Class "StateContext_Class" class (C#)

The demonstration example parses a block of C++ or C# code to remove all
comments.  It ignores comments inside of quotes.  The context maintains an
iterator through the text and an accumulator of comment-free text.  The
context also maintains the current state.  The changes in state are
displayed along the way.

This example also demonstrates a parser that does not use a look-ahead
approach, in which the next character coming is peeked at to determine
which state should be next.  The look-ahead can potentially simplify the
number of states needed but the example would get quite messy with
potentially multiple if statements for each state change.

Note: This example highlights one problem of an object-oriented approach
to a state machine and that is the sheer number of small classes that need
to be managed.  You either get many classes in a single file or many files
each with a small class.


__C++__

@snippet cplusplus/State_Exercise.cpp Using State in C++

__C#__

@snippet csharp/program.cs Using State in C#


### See Also
- @ref mainpage "Main page"
