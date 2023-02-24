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
        static std::shared_ptr<FileDirEntry> rootEntry;

        static FileDirEntry* _FindEntry(std::string filepath);

    public:
        static FileDirEntry* GetEntry(std::string filepath);
    };
} // end namespace

#endif // __COMPOSITE_FILEACCESS_H__

