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
