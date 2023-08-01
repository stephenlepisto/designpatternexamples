/// @file
/// @brief
/// Implementation of the @ref Helpers::argumentinvalid_error "argumentinvalid_error"
/// exception.

#pragma once
#ifndef __ARGUMENT_ERROR_H__
#define __ARGUMENT_ERROR_H__

#include <stdexcept>
#include <string>

namespace Helpers
{

    /// <summary>
    /// Exception for arguments that are invalid.
    /// </summary>
    class argumentinvalid_error : public std::runtime_error
    {
    private:
        std::string _parameter;
    public:
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="parm">The parameter that was invalid.</param>
        /// <param name="what_arg">Specific message indicating the problem.</param>
        argumentinvalid_error(const std::string& parm, const std::string& what_arg)
            : runtime_error(what_arg)
            , _parameter(parm)
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="parm">The parameter that was invalid.</param>
        /// <param name="what_arg">Specific message indicating the problem.</param>
        argumentinvalid_error(const char* parm, const char* what_arg)
            : runtime_error(what_arg)
            , _parameter(parm != nullptr ? parm : "")
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

#endif // __ARGUMENT_ERROR_H__
