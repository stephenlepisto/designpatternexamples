/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Composite_FileAccess "Composite_FileAccess"
/// class used in the @ref composite_pattern.

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif

#include <format> // Requires C++20
#include <filesystem>
#include <system_error>

#include "Composite_FileAccess.h"
#include "helpers/replace.h"
#include "helpers/split.h"
#include "helpers/DateTime.h"
using Helpers::DateTime;

namespace DesignPatternExamples_cpp
{

        // The hardcoded hierarchy representing a file/directory structure.
        // Note: This is the Composite pattern in action.
        std::shared_ptr<FileDirEntry> Composite_FileAccess::rootEntry =
            std::make_shared<DirEntry>("root", DateTime::Now(), FileDirEntryList{
                std::make_shared<FileEntry>("FileA.txt", 101, DateTime::Now()),
                std::make_shared<FileEntry>("FileB.txt", 102, DateTime::Now()),
                std::make_shared<FileEntry>("FileC.txt", 103, DateTime::Now()),
                std::make_shared<DirEntry>("subdir1", DateTime::Now(), FileDirEntryList{
                    std::make_shared<FileEntry>("FileD.txt", 104, DateTime::Now()),
                    std::make_shared<FileEntry>("FileE.txt", 105, DateTime::Now()),
                    std::make_shared<DirEntry>("subdir2", DateTime::Now(), FileDirEntryList{
                        std::make_shared<FileEntry>("FileF.txt", 106, DateTime::Now()),
                        std::make_shared<FileEntry>("FileG.txt", 107, DateTime::Now())
                    }),
                }),
            });


        FileDirEntry* Composite_FileAccess::_FindEntry(std::string filepath)
        {
            FileDirEntry* root = rootEntry.get();

            std::vector<std::string> pathComponents = Helpers::split(filepath, "/");
            size_t numComponents = pathComponents.size();
            for (size_t index = 0; index < numComponents; ++index)
            {
                if (root->Name() != pathComponents[index])
                {
                    // Mismatch in path to this entry, bad path
                    root = nullptr;
                    break;
                }
                if (index + 1 >= numComponents)
                {
                    // Reached end of path so we found what was asked for.
                    break;
                }

                // Still haven't reached end of specified path, look at
                // the current root for children.

                FileDirEntryList children = root->Children();
                if (children.empty())
                {
                    // Path included leaf in the middle, bad path
                    break;
                }

                root = nullptr; // assume we won't find anything
                // Look ahead in the path for a matching child.
                std::string childComponent = pathComponents[index + 1];
                for (FileDirEntryList::iterator childIter = std::begin(children);
                    childIter != std::end(children);
                    childIter++)
                {
                    if (childComponent == (*childIter)->Name())
                    {
                        root = (*childIter).get();
                        break;
                    }
                }
                if (root == nullptr)
                {
                    // Couldn't find matching child, bad path
                    break;
                }
            }

            return root;
        }


        FileDirEntry* Composite_FileAccess::GetEntry(std::string filepath)
        {
            filepath = Helpers::Replace(filepath, '\\', '/');
            FileDirEntry* fileDirEntry = _FindEntry(filepath);

            if (fileDirEntry == nullptr)
            {
                std::string msg = std::format("Unable to find '{0}'", filepath);
                std::error_code errorcode(2, std::generic_category());
                throw std::filesystem::filesystem_error(msg, errorcode);
            }

            return fileDirEntry;
        }

} // end namespace
