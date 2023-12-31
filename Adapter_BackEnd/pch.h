/// @file
/// @brief
/// Header for precompiled headers.  Used only on Windows.
///
/// Files listed here are compiled only once, improving build performance for future builds.
/// This also affects IntelliSense performance, including code completion and many code browsing features.
/// However, files listed here are ALL re-compiled if any one of them is updated between builds.
/// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#ifndef _countof
#define _countof(w) (sizeof(w)/sizeof((w)[0]))
#endif

#endif //PCH_H
