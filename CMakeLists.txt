cmake_minimum_required(VERSION 3.26)

# Must specify languages here as this also locates the support for each
# language.  Calling just
# set_target_properties(DesignPatternExamples_csharp PROPERTIES LINKER_LANGUAGE CSharp)
# in the individual CMakeLists.txt file isn't enough as, in this case, the C#
# compiler was not found.
project(DesignPatternExamples C CXX CSharp)

add_subdirectory(Adapter_BackEnd)
add_subdirectory(c)
add_subdirectory(cplusplus)
add_subdirectory(csharp)
add_subdirectory(python)
add_subdirectory(rust)
add_subdirectory(CreateDocs)

#-----------------------------------------------------------------------------
# The following lists all the targets that can be built.
# (https://stackoverflow.com/questions/37434946/how-do-i-iterate-over-all-cmake-targets-programmatically/62311397#62311397)
function(get_all_targets var)
    set(targets)
    get_all_targets_recursive(targets ${CMAKE_CURRENT_SOURCE_DIR})
    set(${var} ${targets} PARENT_SCOPE)
endfunction()

macro(get_all_targets_recursive targets dir)
    get_property(subdirectories DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirectories})
        get_all_targets_recursive(${targets} ${subdir})
    endforeach()

    get_property(current_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${targets} ${current_targets})
endmacro()

get_all_targets(all_targets)
message("All targets: ${all_targets}")
