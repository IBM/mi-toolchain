/*!
 * Copyright (C) tkornuta, IBM Corporation 2015-2019
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
