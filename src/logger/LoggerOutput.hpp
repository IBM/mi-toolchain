/*!
 * \file LoggerOutput.hpp
 * \brief Contains definition of an abstract logger output class, from which all output classes should be derrived.
 * \author tkornuta
 * \date Dec 1, 2015
 */

#ifndef SRC_CONFIGURATION_LOGGEROUTPUT_HPP_
#define SRC_CONFIGURATION_LOGGEROUTPUT_HPP_

#include <logger/LoggerAux.hpp>


namespace mic {
namespace logger {

/*!
 * \class LoggerOutput
 * \brief Abstract interface for different logger outputs.
 */
class LoggerOutput {
public:
	/*!
	 * Constructor. Sets default severity level (LINFO as default).
	 * @param sev Default output severity level.
	 */
	LoggerOutput(Severity_t sev = LINFO) : lvl(sev)
	{

	}

	/*!
	 * Virtual destructor. Empty.
	 */
	virtual ~LoggerOutput(){}


	/*!
	 * \brief Logs given message.
	 * Depending on actual implementation, it can be printed on terminal, ncurses window, file etc.
	 *
	 * \param msg_ Message to log
	 * \param severity_ Severity of message
	 * \param file_ Name of file, from which log was called
	 * \param line_ Number of line, from which log was called
	 */
	virtual void print(const std::string & msg_, Severity_t severity_, const std::string & file_, int line_) const = 0;

	/*!
	 * Sets severity level.
	 * @param sev Severity level.
	 */
	void setLvl(Severity_t sev) {
		lvl = sev;
	}

	/*!
	 * Increments severity level.
	 */
	void incrementLvl() {
		if (lvl < LFATAL)
			lvl = (Severity_t)(lvl+1);
	}

	/*!
	 * Decrements severity level.
	 */
	void decrementLvl() {
		if (lvl > LTRACE)
			lvl = (Severity_t)(lvl-1);
	}


	/*!
	 * Returns severity level.
	 * @return Severity level
	 */
	Severity_t getLvl() const {
		return lvl;
	}

protected:
	/*!
	 * Logger severity - messages below this level will not be printed.
	 */
	Severity_t lvl;
};



} /* namespace logger */
} /* namespace mic */


#endif /* SRC_CONFIGURATION_LOGGEROUTPUT_HPP_ */
