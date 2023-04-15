/// @file
/// @brief
/// Implementation of the FileDirEntry_GetFileDirType(), FileDirEntry_GetLength(),
/// FileDirEntry_GetChildren(), FileDirEntry_GetName(), and FileDirEntry_GetWhenModified()
/// functions as used in support of the @ref composite_pattern example.

#include "Composite_FileDirEntry.h"


///////////////////////////////////////////////////////////////////////////////
// FileDirEntry_GetFileDirType()
///////////////////////////////////////////////////////////////////////////////
FileDirTypes FileDirEntry_GetFileDirType(FileDirEntry* entry)
{
    FileDirTypes type = FileDirType_Unknown;

    if (entry != NULL)
    {
        type = entry->fileDirType;
    }

    return type;
}

///////////////////////////////////////////////////////////////////////////////
// FileDirEntry_GetLength()
///////////////////////////////////////////////////////////////////////////////
long FileDirEntry_GetLength(FileDirEntry* entry)
{
    long length = 0;

    if (entry->fileDirType == FileDirType_File)
    {
        length = entry->length;
    }
    else if (entry->fileDirType == FileDirType_Directory)
    {
        DirEntry* dirEntry = (DirEntry*)entry;
        if (dirEntry->_lengthSet)
        {
            length = dirEntry->base.length;
        }
        else
        {
            FileDirEntry* child = dirEntry->_children;
            while (child != NULL)
            {
                length += FileDirEntry_GetLength(child);
                child = child->next;
            }
            dirEntry->base.length = length;
            dirEntry->_lengthSet = true;
        }
    }

    return length;
}

///////////////////////////////////////////////////////////////////////////////
// FileDirEntry_GetChildren()
///////////////////////////////////////////////////////////////////////////////
FileDirEntry* FileDirEntry_GetChildren(FileDirEntry* entry)
{
    FileDirEntry* firstChild = NULL;

    if (entry != NULL)
    {
        if (entry->fileDirType == FileDirType_Directory)
        {
            DirEntry* dirEntry = (DirEntry*)entry;
            firstChild = dirEntry->_children;
        }
    }

    return firstChild;
}

///////////////////////////////////////////////////////////////////////////////
// FileDirEntry_GetName()
///////////////////////////////////////////////////////////////////////////////
const char* FileDirEntry_GetName(FileDirEntry* entry)
{
    const char* name = NULL;

    if (entry != NULL)
    {
        name = entry->name;
    }

    return name;
}

///////////////////////////////////////////////////////////////////////////////
// FileDirEntry_GetWhenModified()
///////////////////////////////////////////////////////////////////////////////
time_t FileDirEntry_GetWhenModified(FileDirEntry* entry)
{
    time_t whenModified = 0;

    if (entry != NULL)
    {
        whenModified = entry->whenModified;
    }

    return whenModified;
}
