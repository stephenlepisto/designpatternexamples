# Observer Pattern {#observer_pattern}

@image html observer_diagram.png "Diagram of the Observer pattern"

The Observer pattern is used when one or more entities need to be told
about a change in state of another entity (typically known as the Subject)
and those entities, upon notification, pull data from the Subject to
complete their own specific tasks.  Alternatively, the Subject could push
the data to the observing entities.

The Observer pattern uses a publish/subscribe model, where entities
interested in changes in the Subject subscribe to the Subject for change
notifications.  This allows the Subject to notify multiple subscribers
(observers) about a single change.  It is then up to the observer to do
something in response to the change notification.

One common example of the observer pattern is the View element of the
Model-View-Controller architecture.  In this architecture, the Model holds
all the data, the Controller is the input mediator (yes, an example of the
@ref mediator_pattern) between the Model and the outside world, and the View is
what shows the Model to the outside world.  There can be multiple Views.
When a change occurs in the Model, the Views are notified of the change.
Each View then pulls data from the Model to render that specific view.

At its most general, any event-based system is the Observer pattern in
action.  A subscriber to the event -- the observer -- receives
notifications when something occurs (a change).  The subscriber then reacts
to that event as appropriate.

The Subject typically defines a minimal interface an Observer must
implement to subscribe to change notifications.  This interface can be
literally an interface with one or more methods on it or it could be just a
single function that is called (for a non-object-oriented approach).

The Observer knows what it is observing because it has to not only
subscribe to the Subject but potentially access the Subject for data that
may have changed.  This knowledge of the Subject can be partially mitigated
by defining an interface on the Subject the Observer can use to fetch data
from the Subject.

There are two ways the Observer and the Subject can interact:
 1) The Observer pulls data from the Subject in response to a change
    notification.
 2) The Subject pushes the data to the Observer as part of the change
    notification.

The pull approach can be inefficient if multiple observers are observing
the same Subject.  When each observer gets the change notification, each
observer fetches potentially the same data from the Subject, producing
redundant data fetches.  There is not a lot that can be done about this but
at least the coupling is very loose between the Subject and the observers.

The push approach can be more efficient as the data is part of the change
notification and needs to be computed only once, regardless of the number
of observers.  The question is how much data should be pushed to each
observer and in what form.  This can be made easier if the observers
implement an interface known to the Subject with one or more methods to be
called as part of the process of sending the event notifications.

# How to Use

<table>
<caption>Links to the Observer classes and interfaces</caption>
<tr>
  <th>C++
  <th>C#
  <th>Python
  <th>C
<tr>
  <td>@ref DesignPatternExamples_cpp::IObserverNumberChanged "IObserverNumberChanged" interface
  <td>@ref DesignPatternExamples_csharp.IObserverNumberChanged "IObserverNumberChanged" interface
  <td>@ref DesignPatternExamples_python.observer.observersubject_numberproducer.IObserverNumberChanged "IObserverNumberChanged" interface
  <td>Not Applicable
<tr>
  <td> @ref DesignPatternExamples_cpp::INumberProducer "INumberProducer" interface
  <td>@ref DesignPatternExamples_csharp::INumberProducer "INumberProducer" interface
  <td>@ref DesignPatternExamples_python.observer.observersubject_numberproducer.INumberProducer "INumberProducer" interface
  <td>Not Applicable
<tr>
  <td>@ref DesignPatternExamples_cpp::IEventNotifications "IEventNotifications" interface
  <td>@ref DesignPatternExamples_csharp.IEventNotifications "IEventNotifications" interface
  <td>@ref DesignPatternExamples_python.observer.observersubject_numberproducer.IEventNotifications "IEventNotifications" interface
  <td>Not Applicable
<tr>
  <td>@ref DesignPatternExamples_cpp::ObserverSubject_NumberProducer "ObserverSubject_NumberProducer" class
  <td>@ref DesignPatternExamples_csharp::ObserverSubject_NumberProducer "ObserverSubject_NumberProducer" class
  <td>@ref DesignPatternExamples_python.observer.observersubject_numberproducer.ObserverSubject_NumberProducer "ObserverSubject_NumberProducer" class
  <td>NumberProducer structure<br>
      NumberProducer_Create()<br>
      NumberProducer_Destroy()
<tr>
  <td>@ref DesignPatternExamples_cpp::ObserverForDecimal "ObserverForDecimal" class
  <td>@ref DesignPatternExamples_csharp.ObserverForDecimal "ObserverForDecimal" class
  <td>@ref DesignPatternExamples_python.observer.observer_class.ObserverForDecimal "ObserverForDecimal" class
  <td>ObserverForDecimal_NumberChanged()
<tr>
  <td>@ref DesignPatternExamples_cpp::ObserverForHexaDecimal "ObserverForHexaDecimal" class
  <td>@ref DesignPatternExamples_csharp.ObserverForHexaDecimal "ObserverForHexaDecimal" class
  <td>@ref DesignPatternExamples_python.observer.observer_class.ObserverForHexaDecimal "ObserverForHexaDecimal" class
  <td>ObserverForHexadecimal_NumberChanged()
<tr>
  <td>@ref DesignPatternExamples_cpp::ObserverForBinary "ObserverForBinary" class
  <td>@ref DesignPatternExamples_csharp.ObserverForBinary "ObserverForBinary" class
  <td>@ref DesignPatternExamples_python.observer.observer_class.ObserverForBinary "ObserverForBinary" class
  <td>ObserverForBinary_NumberChanged()
</table>

In this example of the Observer pattern, a Subject contains a numerical
value that can change.  There are three observers to the subject who are
notified whenever the value changes.  Each observer pulls the number from
the Subject (for C++, C#, and Python) or is pushed the number (for C) and then
displays the number in a different base.  Typically these observers would run
on different threads but in the interest of keeping things readable, everything
runs on the same thread.  The order of the output is dictated by the order of
the observers subscribing to the Subject.

*Note: For C++, C#, and Python, this example could be made simpler by having
the Subject push the data to the observers, as shown in the example for C.  I
wanted to show the more complex form of the Observer pattern, however, so I
went with a pull model.*

*As the C example suggests, the push model would have eliminated the need for
the INumberProducer interface on the Subject as well as the need to take and
store the INumberProducer object in each observer.  And that in turn would
simplify each observer class down to a single method to support the
IObserverNumberChanged interface.*


__C++__

@snippet cplusplus/Observer_Exercise.cpp Using Observer in C++

__C#__

@snippet csharp/Observer_Exercise.cs Using Observer in C#

__Python__

@snippet python/DesignPatternExamples_python/observer/observer_exercise.py Using Observer in Python

__C__

@snippet c/Observer_Exercise.c Using Observer in C

__RUST__

(_Apologies.  Doxygen does not understand Rust syntax and therefore cannot colorize the code._)

@snippet rust/design_pattern_examples_rust/src/observer.rs Using Observer in Rust

### See Also
- @ref mainpage "Main page"
