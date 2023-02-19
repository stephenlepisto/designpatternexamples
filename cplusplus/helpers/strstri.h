#ifndef __STRSTRI_H__
#define __STRSTRI_H__

// Do case-insensitive search for string 2 in string 1.
// Similar to strstr().

// In strstri.cpp
char* strstri(
		const char* s1,
		const char* s2);

// In wcsstri.cpp
wchar_t* wcsstri(
		const wchar_t* s1,
		const wchar_t* s2);

#endif // __STRSTRI_H__
