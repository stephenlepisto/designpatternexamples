/// @file
/// @brief
/// Implementation of the @ref Helpers::titlecase "titlecase"() function, for making
/// a word lowercase with the first letter uppercase.

#include <sstream>
#include "titlecase.h"

namespace Helpers
{
    std::string titlecase(const std::string& s)
    {
        std::ostringstream output;

        for (size_t index = 0; index < s.size(); index++)
        {
            int c = s[index];
            // Stop on space or non-alphabetic character (presumably punctuation)
            if (std::isspace(c) || !std::isalpha(c))
            {
                // Reached end of a word, copy rest of string over
                output << s.substr(index);
                // And we are done
                break;
            }

            if (index == 0)
            {
                c = std::toupper(c);
            }
            else
            {
                c = std::tolower(c);
            }
            output << static_cast<char>(c);
        }

        return output.str();
    }

} // end namespace
