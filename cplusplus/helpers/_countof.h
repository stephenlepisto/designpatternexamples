#ifndef ___COUNTOF_H__
#define ___COUNTOF_H__

#include <stdlib.h>
// On Windows, stdlib.h contains a definition of _countof().
// On Linux, this definition does not exist so we need to add one.
#ifndef _countof
#define _countof(w) (sizeof(w) / sizeof((w)[0]))
#endif

#endif // ___COUNTOF_H__
