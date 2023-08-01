/// @file
/// @brief
/// Implementation of the @ref Helpers::split "split" functions, for splitting
/// a narrow character string on delimiters.

#include <cstring>
#include "split.h"

namespace Helpers
{

    // Split the string into multiple strings.
    std::vector<std::string> split(const char* pszString, const char* splitChars/* = " "*/)
    {
        std::vector<std::string> items;
        if (splitChars == NULL || *splitChars == '\0')
        {
            splitChars = " ";
        }

        const char* workPtr = pszString;
        for (;;)
        {
            size_t foundIndex = strcspn(workPtr, splitChars);
            if (foundIndex < strlen(workPtr))
            {
                items.push_back(std::string(workPtr, 0, foundIndex));
                workPtr += foundIndex + 1;
            }
            else
            {
                items.push_back(std::string(workPtr));
                break;
            }
        }
        return items;
    }

    std::vector<std::string> split(const std::string& szString,
        const std::string& splitChars/* = " "*/)
    {
        return split(szString.c_str(), splitChars.c_str());
    }

} // end namespace
