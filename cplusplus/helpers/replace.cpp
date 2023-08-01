/// @file
/// @brief
/// Implementation of the
/// @ref Helpers::Replace(const std::string&, const char*, const char*, bool) "Replace(const std::string&, const char*, const char*, bool)"
/// and
/// @ref Helpers::Replace(const std::string&, char, char, bool) "Replace(const std::string&, char, char, bool)"
/// functions, for replacing narrow character characters and strings in a string.

#include <cstring>

#include "replace.h"
#include "strstri.h"

namespace Helpers
{

	//////////////////////////////////////////////////////////////////////////////
	//
	// Function   : Replace
	//
	// Scope      : Public
	//
	// Arguments  :  s                 = string to search
	//               str1              = pointer to string to search for
	//               str2              = pointer to string to replace with
	//                                   (can be an empty string)
	//               bCaseInsensitive  = true if search is case insensitive
	//                                   false if search is case sensitive
	//                                   (default is false)
	//
	// Returns    : new string containing the changes.
	//
	// Description: Replace all occurrences of string str1 with string str2 in s.
	//              If str1 is empty or either str1 or str2 are null, no
	//              replacement is made.  If str2 is empty then all matches to
	//              str1 are effectively removed from the string.
	//
	// Notes      : I'm using std::string throughout this function despite some
	//              of the obvious inefficiencies.  A more efficient algorithm
	//              would work with a single buffer that increases as necessary
	//              to accommodate the changed string.  However, that means
	//              managing the buffer myself.  So I let std::string do all the
	//              work.
	//
	//////////////////////////////////////////////////////////////////////////////

	std::string  Replace(
			const std::string& s,
			const char* str1,
			const char* str2,
			bool bCaseInsensitive/*=false*/)
	{
		std::string new_string(s);
		size_t str1Len = (str1 != nullptr) ? strlen(str1) : 0;

		// If there is something to do then
		if (!s.empty() && str1Len > 0 && str2 != nullptr)
		{
			bool bReplaced = false;
			std::string out; // build new string here first
			const char* pStart = s.c_str();
			const char* pEnd = pStart + s.length();

			// Start at the beginning of the source string
			// and continue to the end.
			while (pStart < pEnd)
			{
				const char* pFound = nullptr;

				// Look for next occurrence of str1
				if (bCaseInsensitive)
				{
					pFound = strstri(pStart, str1);
				}
				else
				{
					pFound = strstr(pStart, str1);
				}

				// If str1 has been found, replace it
				if (pFound != nullptr)
				{
					// First, append the stuff between the search start
					// and the just found str1
					out.append(pStart, pFound - pStart);
					// "Insert" str2 into the string (this is the replacement)
					out.append(str2);
					// Update the search start to point to after the found str1
					pStart = pFound + str1Len;
					bReplaced = true;
				}
				else
				{
					// str1 not found, copy rest of source to out
					// and terminate the loop.
					if (pStart != nullptr)
					{
						out += pStart;
					}
					pStart = pEnd;
				}
			}

			// If replacements made then set source string to new string.
			if (bReplaced)
			{
				new_string = out;
			}
		}

		return new_string;
	}


	//////////////////////////////////////////////////////////////////////////////
	//
	// Function   : Replace
	//
	// Scope      : Public
	//
	// Arguments  :  s                 = string to search
	//               c1                = character to search for
	//               c2                = character to replace with
	//               bCaseInsensitive  = true if search is case insensitive
	//                                   false if search is case sensitive
	//                                   (default is false)
	//
	// Returns    : new string containing the changes.
	//
	// Description: Replace all occurrences of character c1 with character c2
	//              in s.
	//
	// Notes      : I'm reusing the Replace() for strings instead of
	//              std::replace_if() because using the former is cleaner and
	//              easier to maintain than adding two functors to satisfy the
	//              requirements for std::replace_if().
	//
	//////////////////////////////////////////////////////////////////////////////

	std::string Replace(
			const std::string& s,
			char c1,
			char c2,
			bool bCaseInsensitive/*=false*/)
	{
		std::string str1(1, c1);
		std::string str2(1, c2);
		return (Replace(s, str1.c_str(), str2.c_str(), bCaseInsensitive));
	}
}; // end namespace
