/// @file
/// @brief
/// Implementation of the @ref Helpers::split "split" functions, for splitting
/// a wide character string on delimiters.

#include "split.h"

namespace Helpers
{

    // Split the string into multiple strings.
    std::vector<std::wstring> split(const wchar_t* pszString, const wchar_t* splitChars/* = L" "*/)
    {
        std::vector<std::wstring> items;
        if (splitChars == NULL || *splitChars == L'\0')
        {
            splitChars = L" ";
        }

        const wchar_t* workPtr = pszString;
        for (;;)
        {
            size_t foundIndex = wcscspn(workPtr, splitChars);
            if (foundIndex < wcslen(workPtr))
            {
                items.push_back(std::wstring(workPtr, 0, foundIndex));
                workPtr += foundIndex + 1;
            }
            else
            {
                items.push_back(std::wstring(workPtr));
                break;
            }
        }
        return items;
    }

    std::vector<std::wstring> split(const std::wstring& szString, 
        const std::wstring& splitChars/* = L" "*/)
    {
        return split(szString.c_str(), splitChars.c_str());
    }

} // end namespace
