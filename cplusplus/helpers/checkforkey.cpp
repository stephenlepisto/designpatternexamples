/// @file
/// @brief
/// Implementation of the @ref Helpers::checkforkey "checkforkey()" function
/// for determining if a key has been pressed.

#ifdef _MSC_VER
#include <conio.h>
#endif

#include "checkforkey.h"

/// <summary>
/// The namespace containing all the "helper" functions in the C++ code.
/// </summary>
namespace Helpers
{

    /// <summary>
    /// Determine if a key has been pressed.
    /// </summary>
    /// <returns>Returns true if a key has been pressed; otherwise, returns
    /// false.  Call readkey() to get the actual key.</returns>
    bool checkforkey()
    {
#ifdef _MSC_VER
        return _kbhit() != 0;
#else
        return false;
#endif
    }

} // end namespace
