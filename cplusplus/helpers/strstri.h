/// @file
/// @brief
/// Declaration of the @ref Helpers::strstri "strstri" function, case-insensitive
/// string search for narrow character strings.
/// 
/// Function to search for one string in another in a case-insensitive way
/// (otherwise this is identical to the standard C library function strstr()).

#ifndef __STRSTRI_H__
#define __STRSTRI_H__

namespace Helpers
{

	/// <summary>
	///Do case-insensitive search for string 2 (`s2`) in string 1 (`s1`).
	/// Similar to the C library's strstr().
	/// </summary>
	/// <param name="s1">Pointer to the string to search</param>
	/// <param name="s2">Pointer to the string to search for</param>
	/// <returns>Pointer into the string to search where the first match
	/// was found; otherwise, return nullptr.</returns>
	char* strstri(
		const char* s1,
		const char* s2);

} // end namespace

#endif // __STRSTRI_H__
