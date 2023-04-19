/// @file
/// @brief
/// Declaration of the readkey() function, a blocking read for a key from the
/// keyboard.

#pragma once
#ifndef __READKEY_H__
#define __READKEY_H__

/// <summary>
/// Read a key from the keyboard, blocking if no key is pressed.  Use the
/// checkforkey() function to see if a key has been pressed.
/// </summary>
/// <returns>Returns the ASCII for the key pressed.</returns>
int readkey();


#endif //__READKEY_H__

