/// @file
/// @brief
/// Declaration of the @ref Helpers::wcsstri "wcsstri" function, case-insensitive
/// string search for wide character strings.

#ifndef __WCSSTRIW_H__
#define __WCSSTRIW_H__

namespace Helpers
{
	/// <summary>
	///Do case-insensitive search for string 2 (`s2`) in string 1 (`s1`).
	/// Similar to the C library's wcsstr().
	/// </summary>
	/// <param name="s1">Pointer to the string to search</param>
	/// <param name="s2">Pointer to the string to search for</param>
	/// <returns>Pointer into the string to search where the first match
	/// was found; otherwise, return nullptr.</returns>
	wchar_t* wcsstri(
		const wchar_t* s1,
		const wchar_t* s2);

} // end namespace

#endif // __WCSSTRIW_H__
