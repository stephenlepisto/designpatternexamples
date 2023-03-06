/// @file
/// @brief
/// Implementation of the @ref Helpers::argumentnull_error "argumentnull_error"
/// exception.

#pragma once
#ifndef __ARGUMENTNULL_ERROR_H__
#define __ARGUMENTNULL_ERROR_H__

#include <stdexcept>
#include <string>

namespace Helpers
{
    /// <summary>
    /// Exception for arguments that are null.
    /// </summary>
    class argumentnull_error : public std::runtime_error
    {
    private:
        std::string _parameter;
    public:
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="parm">The parameter that was null.</param>
        /// <param name="what_arg">Specific message indicating the problem.</param>
        argumentnull_error(const std::string& parm, const std::string& what_arg)
            : _parameter(parm)
            , runtime_error(what_arg)
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="parm">The parameter that was null.</param>
        /// <param name="what_arg">Specific message indicating the problem.</param>
        argumentnull_error(const char* parm, const char* what_arg)
            : _parameter(parm != nullptr ? parm : "")
            , runtime_error(what_arg)
        {
        }

        /// <summary>
        /// Retrieve the parameter associated with the exception.
        /// </summary>
        /// <returns>Returns a string containing the name of the parameter.</returns>
        std::string parameter()
        {
            return _parameter;
        }
    };

} // end namespace

#endif // __ARGUMENTNULL_ERROR_H__

