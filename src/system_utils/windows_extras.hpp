/*!
 * \file windows_extras.cpp
 * \brief File containing windows stuff:
 *       1) implementation of usleep
 * \author gwburr
 * \date March 12, 2016
 */


#ifndef SRC_SYSTEM_UTILS_WINDOWS_EXTRAS_HPP_
#define SRC_SYSTEM_UTILS_WINDOWS_EXTRAS_HPP_

#ifdef _WIN32
#include <Windows.h>

#define usleep(waitTime) {\
	LARGE_INTEGER perfCnt, start, now;\
	QueryPerformanceFrequency(&perfCnt);QueryPerformanceCounter(&start);\
	do {\
		QueryPerformanceCounter((LARGE_INTEGER*) &now);\
	} while ((now.QuadPart - start.QuadPart) / float(perfCnt.QuadPart) * 1000 * 1000 < waitTime);\
}

#endif  
#endif