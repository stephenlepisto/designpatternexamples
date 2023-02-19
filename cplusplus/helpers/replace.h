#pragma once
#ifndef __REPLACE_H__
#define __REPLACE_H__

#include <string>

namespace Helpers
{
    // In replace.cpp
    std::string Replace(
            const std::string& s,
            char c1,
            char c2,
            bool bCaseInsensitive = false);

    std::string Replace(
            const std::string& s,
            const char* str1,
            const char* str2,
            bool bCaseInsensitive = false);

    // In replacew.cpp
    std::wstring Replace(
            const std::wstring& s,
            wchar_t c1,
            wchar_t c2,
            bool bCaseInsensitive = false);

    std::wstring Replace(
            const std::wstring& s,
            const wchar_t* str1,
            const wchar_t* str2,
            bool bCaseInsensitive = false);

}; // end namespace Helpers

#endif // __REPLACE_H__
