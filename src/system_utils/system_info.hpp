/*!
 * \file system_info.hpp
 * \brief File containing declarations of functions useful for retrieving system info, such as CPU name, time etc.
 * \author tkornuta
 * \date Dec 4, 2015
 */

#ifndef SRC_SYSTEM_UTILS_SYSTEM_INFO_HPP_
#define SRC_SYSTEM_UTILS_SYSTEM_INFO_HPP_

#include <string>
#include <sys/time.h>

namespace mic {

/**
 * \namespace mic::system_utils
 * \brief Namespace containing system utils (DEPRICATED, to be removed).
 * \author tkornuta
 */
namespace system_utils {

/*!
 * @brief Deletes unnecessary characters from string.
 * @author krocki
 */
std::string delUnnecessary (std::string &str);

/*!
 * Returns first words from string.
 * @author krocki
 */
std::string getFirstWord (std::string &str);


/*!
 * @brief Returns CPU info.
 * @author krocki
 * @return String containing machine name, type etc.
 */
std::string getCPUInfo (void);

/*!
 * @brief Returns current time.
 * @author krocki
 * @return String containing machine name, type etc.
 */
std::string getCurrentTimeInfo (void);

/*!
 * @brief Returns time as a string.
 * @author krocki
 * @return String containing machine name, type etc.
 */
std::string getTimeInfo (const struct timeval & s);

/*!
 * Returns difference between time s and e.
 * @author krocki
 * @param s
 * @param e
 * @return
 */
double getTimeDiff (const struct timeval & s, const struct timeval & e);


}//: namespace system_utils
}//: namespace mic

#endif /* SRC_SYSTEM_UTILS_SYSTEM_INFO_HPP_ */
