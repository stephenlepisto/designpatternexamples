// The Proxy design pattern creates a class as a stand-in for another class
// that might be too large to instantiate all the time or might be implemented
// somewhere else.  The proxy class knows how to instantiate and talk to the
// "real" class and typically does so when the first call on the proxy class
// is made.  This allows the proxy class to be instantiated locally but the
// cost of creating the "real" class is deferred until the proxy class is
// actually used (called on).  There is always a one-to-one relationship
// between the proxy class and the "real" class.
//
// The key to the proxy class is it has the same interface (methods) as the
// "real" class.  All calls made to the proxy class are forwarded to the
// "real" class.  As far as the local program is concerned, the proxy class
// is the real class because the two classes look and act the same.
//
// Proxies are most often seen at either end of a communications channel of
// some kind.  For example, in C#, the remoting channel functionality that
// allows one process to talk to another uses proxy classes on the client end
// of the remoting channel to represent the real classes on the server end.
// When a proxy class is instantiated, information about the remoting channel
// is stashed in the proxy class.  When the first call is made on the proxy
// class, the real class on the server side is instantiated and then the call
// is forwarded to the real class.  The proxy class takes care of
// communicating across the remoting channel to the real class, where the
// actual work is done.  All of this instantiation is taken care of by C#
// itself so the client application only sees what it thinks is the real
// class.
//
// A less well-known use case is for a proxy to represent a class that is
// "expensive" to create and therefore should be deferred until it is actually
// used.  The proxy class is created as usual but as long as it is not
// actually called on, the "expensive" class is not created.  It means the
// program doesn't have to make any special effort to figure out when to call
// the "expensive" class.
//
// The proxy class and the "real" class interfaces are the same to help with
// maintenance.  When a new method is added to the "real" class interface, the
// proxy class also needs to be updated with the new method.  If the two
// classes are in the same process, using an actual interface makes this a lot
// easier to maintain.


using System;


namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents what can be done on the proxy object.
    /// This same interface is implemented on the real object as well to
    /// ensure both have the same methods.  The program accesses the
    /// proxy object only through this interface.
    /// </summary>
    public interface IWorkByProxy
    {
        /// <summary>
        /// Does some work on the given argument and returns a new string.
        /// </summary>
        /// <param name="someArgument">A string to be worked on.</param>
        /// <returns>A string containing the given argument string.</returns>
        string DoWork(string someArgument);
    }


    //========================================================================
    //========================================================================


    /// <summary>
    /// For the purposes of this example, this class encapsulates the real
    /// class and proxy class to hide them from the rest of the example
    /// program.  In a real program, the real class would be in its own
    /// assembly and separate from the proxy class.
    /// </summary>
    static class Proxy_Classes_Container
    {
        /// <summary>
        /// The real class object that does all the work.
        /// 
        /// This would normally be a very expensive class to instantiate and/or
        /// be running on the server end of a remoting channel.  For
        /// demonstration purposes, imagine this class takes many seconds to
        /// instantiate.
        /// </summary>
        private class Real_Class : IWorkByProxy
        {
            //////////////////////////////////////////////////////////////////
            // Implementation of the IWorkByProxy interface
            //////////////////////////////////////////////////////////////////
            string IWorkByProxy.DoWork(string someArgument)
            {
                return String.Format("Real class received '{0}'", someArgument);
            }
        }

        //====================================================================
        //====================================================================


        /// <summary>
        /// The proxy class that implements the IWorkByProxy.
        /// </summary>
        private class Proxy_Class : IWorkByProxy
        {
            // The one and only instance of the real class associated with
            // this proxy class instance.
            IWorkByProxy _realClassInstance;

            /// <summary>
            /// Helper method to retrieve the one and only instance of the
            /// real class.  This hides the details of instantiating the real
            /// class.
            /// </summary>
            /// <returns>A single instance of the real class represented by
            /// the IWorkByProxy interface.</returns>
            private IWorkByProxy _GetRealClass()
            {
                if (_realClassInstance == null)
                {
                    Console.WriteLine("  --> Creating instance of real class...");
                    _realClassInstance = new Real_Class();
                }
                return _realClassInstance;
            }


            //////////////////////////////////////////////////////////////////
            // Implementation of the IWorkByProxy interface
            //////////////////////////////////////////////////////////////////
            
            /// <summary>
            /// Do some work on a string.
            /// </summary>
            /// <param name="someArgument">A string to work on.</param>
            /// <returns>Returns a new string.</returns>
            /// <remarks>
            /// The real class this proxy represents is not instantiated until
            /// this method is called even though the proxy class has been
            /// instantiated.  When this method is called for the first time,
            /// the real class is instantiated, incurring a performance penalty
            /// only on the first call.
            /// </remarks>
            string IWorkByProxy.DoWork(string someArgument)
            {
                Console.WriteLine("  --> proxy class DoWork() in");
                IWorkByProxy realClass = _GetRealClass();
                Console.WriteLine("  --> Forwarding DoWork() call to real class...");
                return realClass.DoWork(someArgument);
            }
        }


        //====================================================================
        //====================================================================


        //////////////////////////////////////////////////////////////////////
        //---------------Public Methods ------------------------------------//
        //////////////////////////////////////////////////////////////////////

        /// <summary>
        /// Retrieve a new instance of the proxy class.
        /// </summary>
        /// <returns>An instance of a proxy class that implements the IWorkByProxy interface.</returns>
        static public IWorkByProxy CreateProxy()
        {
            Console.WriteLine("  --> Creating instance of proxy class...");
            return new Proxy_Class();
        }
    }
}
