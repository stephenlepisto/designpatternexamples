#include <iostream>
#include "cursor.h"

namespace Helpers
{

    void showcursor()
    {
        std::cout << "\x1b[?25h";
        std::cout.flush();
    }
    
    
    void hidecursor()
    {
        std::cout << "\x1b[?25l";
        std::cout.flush();
    }


    void savecursorposition()
    {
        std::cout << "\x1b[s";
        std::cout.flush();
    }
    
    
    void restorecursorposition()
    {
        std::cout << "\x1b[u";
        std::cout.flush();
    }
    
    
    void setcursorposition(int row, int column)
    {
        std::cout << "\x1b[" << row << ";" << column << "H";
        std::cout.flush();
    }

} // end namespace
