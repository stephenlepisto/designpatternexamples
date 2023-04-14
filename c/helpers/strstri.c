/// @file
/// @brief
/// Implementation of the strstri() function, case-insensitive
/// string search for narrow character strings.
/// 
/// Function to search for one string in another in a case-insensitive way
/// (otherwise this is identical to the standard C library function strstr()).

#include <ctype.h>
#include "strstri.h"


	//////////////////////////////////////////////////////////////////////////////
	//
	// Function   : strstri
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
	// Notes      : This is functionally identical to the C Library's strstr()
	//              except for the use of toupper().
	//
	//////////////////////////////////////////////////////////////////////////////

char* strstri(const char* s1, const char* s2)
{
	// Guard against null pointers (strstr() does not do this).
	if (s1 == NULL || s2 == NULL)
	{
		return (NULL);
	}

	// If string to search for is empty, return beginning of str1.
	if (*s2 == '\0')
	{
		return ((char*)s1);
	}

	// Loop over all characters in string to search
	while (*s1 != '\0')
	{
		// Find first occurrence of second string in string 1
		while (*s1 != '\0' && toupper(*s1) != toupper(*s2))
		{
			s1++;
		}

		if (*s1 == '\0')
		{
			break;
		}
		const char* sc1;
		const char* sc2;

		// Now that the first character of string 2 might have been
		// found, compare subsequent characters of string 2 to see
		// if we have an exact match.
		for (sc1 = s1, sc2 = s2; ; )
		{
			if (*++sc2 == '\0')
			{
				// We have reached the end of the string to search for
				// so we must have a match.  Return pointer into s1
				// to the found string.
				return ((char*)s1);
			}
			else
			{
				++sc1;

				if (toupper(*sc1) != toupper(*sc2))
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
	return (NULL);
}
