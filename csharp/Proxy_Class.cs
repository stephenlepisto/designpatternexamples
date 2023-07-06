/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.IWorkByProxy "IWorkByProxy" interface
/// and the @ref DesignPatternExamples_csharp.Proxy_Classes_Container "Proxy_Classes_Container"
/// class used in the @ref proxy_pattern "proxy pattern".

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
            /// <summary>
            /// The one and only instance of the real class associated with
            /// this proxy class instance.
            /// </summary>
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
