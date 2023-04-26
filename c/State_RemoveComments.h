/// @file
/// @brief
/// Declaration of the State_RemoveComments() function that uses a state machine
/// to filter out comments out of a piece of source code, as used in the
/// @ref state_pattern.

#pragma once
#ifndef __STATE_REMOVECOMMENTS_H__
#define __STATE_REMOVECOMMENTS_H__

#include <stdbool.h>
#include "helpers/dynamicstring.h"


/// <summary>
/// Entry point for callers to filter text.  Removes C++-style line and block
/// comments from the text.
/// </summary>
/// <param name="text">The text to filter.</param>
/// <param name="filteredText">A DynamicString that returns the filtered text.
/// </param>
/// <returns>Returns true if the text was filtered successfully, otherwise,
/// returns false if an out of memory condition occurs (or a NULL argument).
/// </returns>
bool State_RemoveComments(const char* text, DynamicString* filteredText);


#endif // __STATE_REMOVECOMMENTS_H__

