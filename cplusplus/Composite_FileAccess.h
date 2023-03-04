/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::Composite_FileAccess "Composite_FileAccess"
/// class used in the @ref composite_pattern "Composite pattern".

#pragma once
#ifndef __COMPOSITE_FILEACCESS_H__
#define __COMPOSITE_FILEACCESS_H__

#include <memory>
#include "Composite_FileDirEntry.h"

namespace DesignPatternExamples_cpp
{

    class Composite_FileAccess
    {
    private:
        /// <summary>
        /// List of all "files" and "directories" used in the
        /// @ref command_pattern "Composite pattern" example.
        /// </summary>
        static std::shared_ptr<FileDirEntry> rootEntry;

        /// <summary>
        /// Helper method to search the static data list for the specified
        /// file/dir entry.
        /// </summary>
        /// <param name="filepath">A "path" specifying the entry to find, with each
        /// component separated by '/'.</param>
        /// <returns>Returns the found entry; otherwise, returns null.</returns>
        static FileDirEntry* _FindEntry(std::string filepath);

    public:
        /// <summary>
        /// Return a FileDirEntry object representing the specified file "path"
        /// in an internal list of data entries that is organized in a file/
        /// directory structure.
        /// </summary>
        /// <param name="filepath">A "path" specifying the entry to find, with each
        /// component separated by '/'.</param>
        /// <returns>Returns a FileDirEntry object representing the specified file entry.
        /// </returns>
        /// <exception cref="FIleNotFoundException">The specified file entry was not found.</exception>
        static FileDirEntry* GetEntry(std::string filepath);
    };
} // end namespace

#endif // __COMPOSITE_FILEACCESS_H__

