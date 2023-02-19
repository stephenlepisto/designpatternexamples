#ifndef __WCSSTRIW_H__
#define __WCSSTRIW_H__

namespace Helpers
{
	// Do case-insensitive search for string 2 in string 1.
	// Similar to strstr().

	wchar_t* wcsstri(
		const wchar_t* s1,
		const wchar_t* s2);

} // end namespace

#endif // __WCSSTRIW_H__
