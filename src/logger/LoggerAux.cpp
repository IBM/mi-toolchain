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
 * \file LoggerAux.cpp
 * \brief Contains definitions of logger auxiliary functions.
 * \author tkornuta
 * \date Dec 1, 2015
 */

#include <logger/LoggerAux.hpp>


namespace mic {
namespace logger {


std::string sev2str(Severity_t sev_)
{
	switch(sev_) {
	case(Trace):
		return "TRACE";
	case(Debug):
		return "DEBUG";
	case(Info):
		return "INFO";
	case(Notice):
		return "NOTICE";
	case(Status):
		return "STATUS";
	case(Warning):
		return "WARNING";
	case(Error):
		return "ERROR";
	case(Fatal):
		return "FATAL";
	}
	return "UNDEFINED";
}


} /* namespace logger */
} /* namespace mic */
