cmake_minimum_required(VERSION 3.26)

# Must specify required languages in the project() command as that locates the
# support for each language.  Calling just
# set_target_properties(DesignPatternExamples_csharp PROPERTIES LINKER_LANGUAGE CSharp)
# in the individual CMakeLists.txt file isn't enough as, in this case, the C#
# compiler was not found.

# Using separate projects allows me to set project-specific version numbers
# here rather than in the source.  It's a bit cumbersome getting the project
# versions into the source code for inclusion in each program but at least
# there is only one place the version is specified.  How the versions are
# stored in each application is up to that application's CMakeLists.txt file,
# the language being used, and the operating system being targeted.

set(PRODUCT_VERSION_MAJOR 1)
set(PRODUCT_VERSION_MINOR 0)
set(PRODUCT_VERSION_PATCH 0)
set(PRODUCT_VERSION_TWEAK 0)
set(PRODUCT_VERSION ${PRODUCT_VERSION_MAJOR}.${PRODUCT_VERSION_MINOR}.${PRODUCT_VERSION_PATCH}.${PRODUCT_VERSION_TWEAK})

project(Adapter_BackEnd LANGUAGES C VERSION 1.0.0.0)
add_subdirectory(Adapter_BackEnd)

project(DesignPatternExamples_CreateDocs VERSION 1.0.0.0)
add_subdirectory(CreateDocs)

project(DesignPatternExamples_c LANGUAGES C VERSION 1.0.0.0)
add_subdirectory(c)

project(DesignPatternExamples_cpp LANGUAGES CXX VERSION 1.0.0.0)
add_subdirectory(cplusplus)

set(CSHARP_PROJECT_VERSION 1.0.0.0)
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
    project(DesignPatternExamples_csharp LANGUAGES CSharp VERSION ${CSHARP_PROJECT_VERSION})
else()
    project(DesignPatternExamples_csharp LANGUAGES VERSION ${CSHARP_PROJECT_VERSION})
endif()
    SET(CMAKE_DOTNET_TARGET_FRAMEWORK "net7.0")
    add_subdirectory(csharp)

project(DesignPatternExamples_python VERSION 1.0.0.0)
add_subdirectory(python)

project(DesignPatternExamples_rust VERSION 1.0.0.0)
add_subdirectory(rust)

# This sets the name of the overall solution file in Visual Studio.
project(DesignPatternExamples)


#-----------------------------------------------------------------------------
# The following lists all the targets that can be built.  Useful for debugging.
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
