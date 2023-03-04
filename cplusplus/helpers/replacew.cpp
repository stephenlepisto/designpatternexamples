/// @file
/// @brief
/// Implementation of the
/// @ref Helpers::Replace(const std::wstring&, const wchar_t*, const wchar_t*, bool) "Replace(const std::wstring&, const wchar_t*, const wchar_t*, bool)"
/// and
/// @ref Helpers::Replace(const std::wstring&, wchar_t, wchar_t, bool) "Replace(const std::wstring&, wchar_t, wchar_t, bool)"
/// functions, for replacing narrow character characters and strings in a string.

#include "replace.h"
#include "wcsstri.h"

namespace Helpers
{

	//////////////////////////////////////////////////////////////////////////////
	//
	// Function   : Replace
	//
	// Scope      : Public
	//
	// Arguments  :  s                 = wstring to search
	//               str1              = pointer to wstring to search for
	//               str2              = pointer to wstring to replace with
	//                                   (can be an empty wstring)
	//               bCaseInsensitive  = true if search is case insensitive
	//                                   false if search is case sensitive
	//                                   (default is false)
	//
	// Returns    : new string containing the changes.
	//
	// Description: Replace all occurrences of wstring str1 with wstring str2 in s.
	//              If str1 is empty or either str1 or str2 are null, no
	//              replacement is made.  If str2 is empty then all matches to
	//              str1 are effectively removed from the wstring.
	//
	// Notes      : I'm using std::wstring throughout this function despite some
	//              of the obvious inefficiencies.  A more efficient algorithm
	//              would work with a single buffer that increases as necessary
	//              to accommodate the changed wstring.  However, that means
	//              managing the buffer myself.  So I let std::wstring do all the
	//              work.
	//
	//////////////////////////////////////////////////////////////////////////////

	std::wstring Replace(
			const std::wstring& s,
			const wchar_t* str1,
			const wchar_t* str2,
			bool bCaseInsensitive/*=false*/)
	{
		std::wstring new_string(s);
		size_t str1Len = (str1 != nullptr) ? wcslen(str1) : 0;

		// If there is something to do then
		if (!s.empty() && str1Len > 0 && str2 != nullptr)
		{
			bool bReplaced = false;
			std::wstring out; // build new wstring here first
			const wchar_t* pStart = s.c_str();
			const wchar_t* pEnd = pStart + s.length();

			// Start at the beginning of the source wstring
			// and continue to the end.
			while (pStart < pEnd)
			{
				const wchar_t* pFound = nullptr;

				// Look for next occurrence of str1
				if (bCaseInsensitive)
				{
					pFound = wcsstri(pStart, str1);
				}
				else
				{
					pFound = wcsstr(pStart, str1);
				}

				// If str1 has been found, replace it
				if (pFound != nullptr)
				{
					// First, append the stuff between the search start
					// and the just found str1
					out.append(pStart, pFound - pStart);
					// "Insert" str2 into the wstring (this is the replacement)
					out.append(str2);
					// Update the search start to point to after the found str1
					pStart = pFound + str1Len;
					bReplaced = true;
				}
				else
				{
					// str1 not found, copy rest of source to out
					// and terminate the loop.
					out += pStart;
					pStart = pEnd;
				}
			}

			// If replacements made then set source wstring to new wstring.
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
	// Arguments  :  s                 = wstring to search
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

	std::wstring Replace(
			const std::wstring& s,
			wchar_t c1,
			wchar_t c2,
			bool bCaseInsensitive/*=false*/)
	{
		std::wstring str1(1, c1);
		std::wstring str2(1, c2);
		return (Replace(s, str1.c_str(), str2.c_str(), bCaseInsensitive));
	}
}; // end namespace
