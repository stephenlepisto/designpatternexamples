/// @file
/// @brief
/// Declaration of the enableVTMode() function
/// for configuring standard input to support the virtual terminal mode (on Windows).

#pragma once
#ifndef __ENABLEVTMODE_H__
#define __ENABLEVTMODE_H__

/// <summary>
/// Enables the virtual terminal processing mode on the current Windows
/// Console.  When the program ends, the state of the processing mode is
/// restored to what it was before we got to it.
/// 
/// This is for Windows only.  Although the mode is enabled in all kinds of
/// Windows console windows (terminal, powershell, etc.), only the Windows
/// Command Prompt needs it; but it doesn't hurt to set it on the others
/// (it's already set on those others).
/// </summary>
/// <remarks>This function uses an atexit() function to restore the mode on
/// program exit.</remarks>
void enableVTMode();


#endif // __ENABLEVTMODE_H__

