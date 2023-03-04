/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::IWorkByProxy "IWorkByProxy"
/// interface and the
/// @ref DesignPatternExamples_cpp::Proxy_Classes_Container "Proxy_Classes_Container"
/// class used in the @ref proxy_pattern "Proxy pattern"

#pragma once
#ifndef __PROXY_CLASS_H__
#define __PROXY_CLASS_H__

#include <memory>
#include <string>

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents what can be done on the proxy object.
    /// This same interface is implemented on the real object as well to
    /// ensure both have the same methods.  The program accesses the
    /// proxy object only through this interface.
    /// </summary>
    struct IWorkByProxy
    {
        virtual ~IWorkByProxy() {}

        /// <summary>
        /// Does some work on the given argument and returns a new std::string.
        /// </summary>
        /// <param name="someArgument">A string to be worked on.</param>
        /// <returns>A string containing the given argument std::string.</returns>
        virtual std::string DoWork(std::string someArgument) = 0;
    };


    //========================================================================
    //========================================================================


    /// <summary>
    /// For the purposes of this example, this class hides the details about
    /// the proxy class and the real class, exposing only the IWorkByProxy
    /// interface of the proxy.  In a real program, the real class would be in
    /// its own application/DLL/assembly and separate from the proxy class.
    /// </summary>
    class Proxy_Classes_Container
    {
    public:
        /// <summary>
        /// Retrieve a new instance of the proxy class.
        /// </summary>
        /// <returns>An instance of a proxy class that implements the IWorkByProxy interface.</returns>
        static std::unique_ptr<IWorkByProxy> CreateProxy();
    };

} // end namespace


#endif // __PROXY_CLASS_H__

