/// @file
/// @brief
/// Declaration of the STRDUP macro that hides the differences between how
/// strdup() is declared in different operating systems.

#pragma once
#ifndef __STRDUP_H__
#define __STRDUP_H__

#include <string.h>

#ifdef _MSC_VER
/// Define STRDUP to be the operating system-specific version of strdup().
#  define STRDUP _strdup
#else
/// Define STRDUP to be the operating system-specific version of strdup().
#define STRDUP strdup
#endif

#endif // __STRDUP_H__
