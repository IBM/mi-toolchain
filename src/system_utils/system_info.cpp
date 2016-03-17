/*!
 * \file system_info.cpp
 * \brief File containing definitions of functions useful for retrieving system info, such as CPU name, time etc.
 * \author tkornuta
 * \date Dec 4, 2015
 */

#include <system_utils/system_info.hpp>

#ifdef __APPLE__
#include <sys/sysctl.h>
#endif

#include <fstream>
#include <sstream>
#include <sys/time.h>

namespace mic {
namespace system_utils {

std::string delUnnecessary (std::string &str) {
    size_t size = str.length();

    for (unsigned j = 0; j <= size; j++) {
        for (unsigned i = 0; i <= j; i++) {

            if (str[i] == ' ' && str[i + 1] == ' ') {
                str.erase (str.begin() + (int)i);
            } else if (str[0] == ' ') {
                str.erase (str.begin() );
            } else if (str[i] == '\0' && str[i - 1] == ' ') {
                str.erase (str.end() - 1);
            }//: elseif
        }//: for
    }//: for
    return str;
}

std::string getFirstWord (std::string &str) {
    return str.substr (0, str.find (' ') );
}

std::string getCPUInfo (void) {

    std::string line;

#ifdef __APPLE__
    char buf[100];
    size_t buflen = 100;
    sysctlbyname ("machdep.cpu.brand_string", &buf, &buflen, NULL, 0);
    std::string info = std::string (buf);
    return delUnnecessary (info);

    #elif __linux__
    std::ifstream finfo ("/proc/cpuinfo");
    while (getline (finfo, line) ) {
        std::stringstream str (line);
        std::string itype;
        std::string info;
        if ( getline ( str, itype, ':' ) && getline (str, info) && itype.substr (0, 10) == "model name" ) {
            return delUnnecessary (info);
        }//: if
    }//: while
#else
    return std::string ("missing cpu name");
#endif
}

std::string getCurrentTimeInfo (void) {
	// Get time.
    struct timeval s;
    gettimeofday (&s, NULL);
    return getTimeInfo(s);
}

std::string getTimeInfo (const struct timeval & s) {
    time_t tt = (time_t) s.tv_sec;

    struct tm *sec;
    sec = localtime (&tt);

	char value[50];
	sprintf(value, "[%04d/%02d/%02d %02d:%02d:%02d.%06ld]", sec->tm_year + 1900, sec->tm_mon + 1, sec->tm_mday, sec->tm_hour, sec->tm_min, sec->tm_sec, (long) s.tv_usec);
	return std::string(value);
}

double getTimeDiff (const struct timeval & s, const struct timeval & e) {

    // computes time difference between s and e
    struct timeval  diff_tv;

    diff_tv.tv_usec = e.tv_usec - s.tv_usec;
    diff_tv.tv_sec = e.tv_sec - s.tv_sec;

    if (s.tv_usec > e.tv_usec) {
        diff_tv.tv_usec += 1000000;
        diff_tv.tv_sec--;
    }

    return (double) diff_tv.tv_sec + ( (double) diff_tv.tv_usec / 1000000.0);
}



}//: namespace system_utils
}//: namespace mic



