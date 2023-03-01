#pragma once
#ifndef __CURSOR_H__
#define __CURSOR_H__

namespace Helpers
{

    /// <summary>
    /// Move the text cursor to the specified screen coordinates.
    /// </summary>
    /// <param name="row">Row index from top, starting at 0.</param>
    /// <param name="column">Column index from left, starting at 0</param>
    void setcursorposition(int row, int column);

    /// <summary>
    /// Retrieve the current cursor position in the console window.
    /// </summary>
    /// <param name="row">Returns the row index from the top, starting at 0.</param>
    /// <param name="column">Returns the column index from the left, starting
    /// at 0.</param>
    void getcursorposition(int* row, int* column);

} // end namespace

#endif // __CURSOR_H__
