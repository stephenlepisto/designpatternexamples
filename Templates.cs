// The Template pattern is used when a single algorithm needs to provide
// access points, otherwise known as hooks, to customize the algorithm for
// a particular task.
//
// C++ has formalized the concept of templates to the point that programs can
// be written in the template "language" itself.  In C++, a template is a
// piece of code where certain types are replaced by a "stand-in" type known
// as a template type.  When the template code, be it a class or function, is
// instantiated or used, the compiler is told the specific type to use for the
// template type and the code is then created at compile time for that
// type.  If a template function is called with three different types, three
// different versions of the function is created, one for each type.  What the
// code does is the same in each case, it's just the types that are different.
//
// In C++, it's possible to substitute functions as well, by providing
// user-defined classes as a template type.  As long as the user-defined class
// conforms to the method calls expected by the template function, the class
// can override or replace functionality expected by the function.
//
// C# introduced the concept of generics to accomplish roughly the same thing,
// again oriented around types.
//
// The Template pattern is a general process of modifying an algorithm so that
// one or more parts of the algorithm can be changed out for some other
// functionality that the algorithm can work with.
//
// The simplest form of a template pattern implementation is the qsort()
// function in the C library.  The qsort() function takes a pointer to another
// function that does the actual comparison between any two elements in the
// list being sorted.  This comparison function is a hook in the qsort
// algorithm, allowing the final order of the objects to be determined at run-
// time by simply substituting a comparison function with another such
// function.  In C++, the Standard Template Library (STL) allows for this same
// kind of substitution on the std::sort() function as well as on many of the
// other algorithms provided by the STL.
//
// The C# library has similar hooks into the various containers such as List,
// Array, and Dictionary.
//
// The Template pattern is generally used where large and complex algorithms
// need to be modified at runtime to suit some particular purpose.  For
// example, a program that displays and executes menus implements a single
// algorithm for displaying and selecting a menu using a mouse.  The algorithm
// can look something like this for a menu-driven display:
//  1. Handle Mouse down on a top-level menu hotspot
//  2. Get a list of menu items to display
//  3. Display each menu item
//  4. Wait for mouse up on a menu item
//  5. Call handler for the specified menu item
//  6. Done
//
// The order of the steps in the algorithm doesn't change, it's just that some
// steps can be altered or added to.  For example, the first "hook" in this
// Template algorithm is used in step 2 to retrieve all the menu items for the
// selected top-level menu.  The second hook can be in step 3, if the
// algorithm provides a customizable display of a menu item such as showing an
// icon (the hook would be to get the icon).  Step 5 uses a third hook to do
// something in response to selecting a menu item.
//
// An additional hook could be added to step 4 to alter the display of a menu
// item when the mouse cursor moves over it, for example, highlighting the
// menu item.  It all depends on the level of customization desired for a
// particular algorithm.
//
// A note of caution: The more hooks that are added to an algorithm, the
// harder it can be to follow what the algorithm is doing, especially in terms
// of handling errors caused by the hooks.  Also, each hook presents yet one
// more source of bugs that have to be dealt with.
//
// There are any number of ways of implementing a hook in an algorithm with
// the choice generally controlled by who is using the algorithm.  In general,
// the hook is written in a coding language and executed at a particular point
// in the algorithm.  One approach in object-oriented languages is to provide
// an interface for each hook.  The user of the algorithm provides a class
// that implements the interface and passes the instance of that interface to
// the algorithm for use.  If the algorithm provides multiple hooks, perhaps a
// single interface with multiple methods, one for each hook, can be provided.
//
// Alternatively, a function can be passed to the algorithm, one function for
// each hook.  This tends to be more functionally oriented but that line is
// blurred by lambdas, which are treated a lot like an object.  In python,
// a function actually is a first-class object.
//
// One final approach to a Template design is to have the hooks implemented in
// a scripting language, either a well-known language or a custom language for
// the application.  The user of the algorithm then provides "scripts" for
// each hook.  By having these "scripts" exposed outside the application, the
// user of the application itself can customize the behavior of the algorithm
// without having to rebuild the application.
//
// The Template pattern differs from the Strategy pattern by the level of
// substitution being provided.  The Template pattern provides hooks into a
// single algorithm whereas the Strategy pattern replaces the entire
// algorithm.
//
// There is also some degree of crossover with the Observer pattern when
// coupled with a framework such as the Model-View-Controller (MVC) framework.
// The MVC framework is an algorithm describing how a Model and Controller
// work with Views.  The Views -- Observers -- are the hooks into the flow
// between Model and Controller.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples
{
    class Templates
    {
    }
}
