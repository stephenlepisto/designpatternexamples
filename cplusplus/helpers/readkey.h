#pragma once
#ifndef __READKEY_H__
#define __READKEY_H__

namespace Helpers
{
    /// <summary>
    /// Read a key from the keyboard, blocking if no key is pressed.
    /// </summary>
    /// <returns>Returns the ASCII for the key pressed.</returns>
    int readkey();

} // end namespace

#endif //__READKEY_H__

