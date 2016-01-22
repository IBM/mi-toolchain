/*!
 * \file LoggerAux.hpp
 * \brief Contains declarations of logger auxiliary functions, macros and severity type.
 * \author tkornuta
 * \date Dec 1, 2015
 */

#ifndef SRC_CONFIGURATION_LOGGERAUX_HPP_
#define SRC_CONFIGURATION_LOGGERAUX_HPP_

#include <string>

namespace mic {
namespace logger {

/*!
 * \brief Message severity level.
 * \author tkornuta
 */
enum Severity_t
{
	Trace = 0, ///< Trace program execution, prints file name and line, typically logged when entering function.
	Debug, ///< Debug message with file and line number, contain user defined debug information.
	Notice, ///< Information, contain user defined information, with small importance.
	Info, ///< Information, contain user defined information.
	Status, ///< Status, contains statuses such as status of application, phase of operation etc.
	Warning, ///< Warning, continue execution
	Error, ///< Something bad happened, try to terminate
	Fatal ///< Something very bad happened, no chance to continue execution
};

/*!
 * Returns string representing the severity level.
 */
std::string sev2str(Severity_t sev_);

#define LTRACE    mic::logger::Trace
#define LDEBUG    mic::logger::Debug
#define LNOTICE     mic::logger::Notice
#define LINFO     mic::logger::Info
#define LSTATUS     mic::logger::Status
#define LWARNING  mic::logger::Warning
#define LERROR    mic::logger::Error
#define LFATAL    mic::logger::Fatal


} /* namespace logger */
} /* namespace mic */


#endif /* SRC_CONFIGURATION_LOGGERAUX_HPP_ */
