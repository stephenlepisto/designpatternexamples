#include <ctype.h>
#include "wcsstri.h"

namespace Helpers
{
    //////////////////////////////////////////////////////////////////////////////
    //
    // Function   : wcsstri
    //
    // Scope      : Public
    //
    // Arguments  :  str1              = pointer to string to search in
    //               str2              = pointer to string to search for
    //
    // Returns    : Pointer into str1 to first character of found str2 or
    //              nullptr if str2 is not found in str1.
    //
    // Description: Find string str2 in string str1, returning pointer to first
    //              occurrence of str2.  Returns nullptr if str2 not found in str1.
    //
    // Notes      : This is functionally identical to the C Library's wcsstr()
    //              except for the use of towupper().
    //
    //////////////////////////////////////////////////////////////////////////////
    wchar_t* wcsstri(
        const wchar_t* s1,
        const wchar_t* s2)
    {
        // Guard against null pointers (wcsstr() does not do this).
        if (s1 == nullptr || s2 == nullptr)
        {
            return (nullptr);
        }

        // If string to search for is empty, return beginning of str1.
        if (*s2 == L'\0')
        {
            return ((wchar_t*)s1);
        }

        // Loop over all characters in string to search
        while (*s1 != L'\0')
        {
            // Find first occurrence of second string in string 1
            while (*s1 != L'\0' && towupper(*s1) != towupper(*s2))
            {
                s1++;
            }

            if (*s1 == L'\0')
            {
                break;
            }
            const wchar_t* sc1;
            const wchar_t* sc2;

            // Now that the first character of string 2 might have been
            // found, compare subsequent characters of string 2 to see
            // if we have an exact match.
            for (sc1 = s1, sc2 = s2; ; )
            {
                if (*++sc2 == L'\0')
                {
                    // We have reached the end of the string to search for
                    // so we must have a match.  Return pointer into s1
                    // to the found string.
                    return ((wchar_t*)s1);
                }
                else
                {
                    ++sc1;

                    if (towupper(*sc1) != towupper(*sc2))
                    {
                        // a character in string 2 doesn't match so start
                        // the whole thing over with the next character
                        // in string 1.
                        break;
                    }
                }
            }
            ++s1;
        }
        // If we get here, there is no match so return nullptr.
        return (nullptr);
    }
} // end namespace
