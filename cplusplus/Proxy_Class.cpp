/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::IWorkByProxy "IWorkByProxy"
/// interface and the
/// @ref DesignPatternExamples_cpp::Proxy_Classes_Container "Proxy_Classes_Container"
/// class used in the @ref proxy_pattern

#include <iostream>
#include <memory>

#include "helpers/formatstring.h"

#include "Proxy_Class.h"

/// <summary>
/// Hides the details of the proxy and real class in C++.
/// Used by the Proxy pattern example.
/// </summary>
namespace Proxy_Class_Private
{
    // For the purposes of this example, this namespace encapsulates the real
    // class and proxy class to hide them from the rest of the example
    // program.  In a real program, the real class would be in its own
    // assembly and separate from the proxy class.


    /// <summary>
    /// The real class object that does all the work.
    /// 
    /// This would normally be a very expensive class to instantiate and/or
    /// be running on the server end of a remoting channel.  For
    /// demonstration purposes, imagine this class takes many seconds to
    /// instantiate.
    /// </summary>
    class Real_Class : public DesignPatternExamples_cpp::IWorkByProxy
    {
    public:
        //////////////////////////////////////////////////////////////////
        // Implementation of the IWorkByProxy interface
        //////////////////////////////////////////////////////////////////
        std::string DoWork(std::string someArgument)
        {
            return Helpers::formatstring("Real class received '%s'", someArgument.c_str());
        }
    };

    //====================================================================
    //====================================================================


    /// <summary>
    /// The proxy class that implements the IWorkByProxy.
    /// </summary>
    class Proxy_Class : public DesignPatternExamples_cpp::IWorkByProxy
    {
    private:
        /// The one and only instance of the real class associated with this proxy class instance.
        std::unique_ptr<DesignPatternExamples_cpp::IWorkByProxy> _realClassInstance;

        /// <summary>
        /// Helper method to retrieve the one and only instance of the
        /// real class.  This hides the details of instantiating the real
        /// class.
        /// </summary>
        /// <returns>A single instance of the real class represented by
        /// the IWorkByProxy interface.</returns>
        DesignPatternExamples_cpp::IWorkByProxy* _GetRealClass()
        {
            if (_realClassInstance == nullptr)
            {
                std::cout << "  --> Creating instance of real class..." << std::endl;
                _realClassInstance = std::make_unique<Real_Class>();
            }
            return _realClassInstance.get();
        }


    public:
        //////////////////////////////////////////////////////////////////
        // Implementation of the IWorkByProxy interface
        //////////////////////////////////////////////////////////////////

        /// <summary>
        /// Do some work on a std::string.
        /// </summary>
        /// <param name="someArgument">A std::string to work on.</param>
        /// <returns>Returns a new std::string.</returns>
        /// <remarks>
        /// The real class this proxy represents is not instantiated until
        /// this method is called even though the proxy class has been
        /// instantiated.  When this method is called for the first time,
        /// the real class is instantiated, incurring a performance penalty
        /// only on the first call.
        /// </remarks>
        std::string DoWork(std::string someArgument)
        {
            std::cout << "  --> proxy class DoWork() in" << std::endl;
            DesignPatternExamples_cpp::IWorkByProxy* realClass = _GetRealClass();
            std::cout << "  --> Forwarding DoWork() call to real class..." << std::endl;
            return realClass->DoWork(someArgument);
        }
    };

} // end Proxy_Class_Private namespace


//============================================================================
//============================================================================


namespace DesignPatternExamples_cpp
{
    std::unique_ptr<IWorkByProxy> Proxy_Classes_Container::CreateProxy()
    {
        std::cout << "  --> Creating instance of proxy class..." << std::endl;
        return std::make_unique<Proxy_Class_Private::Proxy_Class>();
    }

} // end namespace

