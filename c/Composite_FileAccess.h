/// @file
/// @brief
/// Declaration of the Composite_FileAccess_GetEntry() function
/// used in the @ref composite_pattern.

#pragma once
#ifndef __COMPOSITE_FILEACCESS_H__
#define __COMPOSITE_FILEACCESS_H__

#include "Composite_FileDirEntry.h"

/// <summary>
/// Return a FileDirEntry object representing the specified file "path"
/// from an internal list of data entries that is organized in a file/
/// directory structure.
/// </summary>
/// <param name="path">A "path" specifying the entry to find, with each
/// component separated by '/'.</param>
/// <returns>Returns a FileDirEntry object representing the specified file entry.
/// Returns NULL if no entry could be found.
/// </returns>
FileDirEntry* Composite_FileAccess_GetEntry(const char* path);

#endif // __COMPOSITE_FILEACCESS_H__

