#pragma once
#ifndef __CURSOR_H__
#define __CURSOR_H__

namespace Helpers
{

    /// <summary>
    /// Show the text cursor in the console window.
    /// </summary>
    void showcursor();

    /// <summary>
    /// Hide the text cursor in the console window.
    /// </summary>
    void hidecursor();

    /// <summary>
    /// Save the current cursor position to memory.
    /// </summary>
    void savecursorposition();

    /// <summary>
    /// Restore the current cursor position from memory.
    /// </summary>
    void restorecursorposition();

    /// <summary>
    /// Move the text cursor to the specified screen coordinates.
    /// </summary>
    /// <param name="row">Row index from top, starting at 0.</param>
    /// <param name="column">Column index from left, starting at 0</param>
    void setcursorposition(int row, int column);

} // end namespace

#endif // __CURSOR_H__

