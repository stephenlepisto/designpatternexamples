#pragma once
#ifndef __SLEEP_H__
#define __SLEEP_H__

namespace Helpers
{
    /// <summary>
    /// Sleep for the specified number of milliseconds.  Does not return until
    /// after the sleep period.
    /// </summary>
    /// <param name="milliseconds">Number of milliseconds to sleep.</param>
    void sleep(int milliseconds);

} // end namespace

#endif // __SLEEP_H__

