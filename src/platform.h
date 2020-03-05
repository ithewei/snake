#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef __unix__
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

void msleep(int ms) {
#ifdef __unix__
    usleep(1000*ms);
#endif

#ifdef _WIN32
    Sleep(ms);
#endif
}

#endif  // _PLATFORM_H_

