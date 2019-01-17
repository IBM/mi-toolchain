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
 * \file ScopeLogger.hpp
 * \brief Contains definition of ScopeLogger class.
 * \author tkornuta
 * \date Dec 1, 2015
 */


#ifndef SCOPELOGGER_HPP_
#define SCOPELOGGER_HPP_

#include <logger/Logger.hpp>

namespace mic {
namespace logger {

/*!
 * \class ScopeLogger
 * \brief Small class used to prepare line for logger.
 * Object created only for the purpose of parsing the ostringstream, during the macro LOG call.
 */
class ScopeLogger
{
public:
	/*!
	 * Constructor.
	 * @param p_ Parent - "main" logger object.
	 * @param f_ Name of the file which called the logger.
	 * @param l_ Number of the file line in which the logger was called.
	 * @param s_ Log severity level.
	 */
	ScopeLogger(Logger * p_, const std::string & f_, int l_, Severity_t s_) :
		parent(p_), file(f_), line(l_), severity(s_)
	{

	}

	/*!
	 * Destructor. Passes the retrieved data to parent logger.
	 */
	~ScopeLogger() {
		parent->log(file, line, severity, os.str());
	}

	/*!
	 * Returns the ostringstream object to which user can write.
	 */
	std::ostringstream& get()
	{
		return os;
	}

protected:
	/*!
	 * Ostringstream object storing the user comment.
	 */
	std::ostringstream os;

private:
	/*!
	 * Default private constructor - sets parent
	 * @param rhs
	 */
	ScopeLogger(const ScopeLogger & rhs) : parent(rhs.parent) {
		line = -1;
		severity = LTRACE;
	}

	ScopeLogger& operator =(const ScopeLogger&) {
		return *this;
	}

private:
	/// Parent class, to which the information will be sent.
	Logger * parent;

	/// Name of the file which called the logger.
	const std::string file;

	/// Number of the file line in which the logger was called.
	int line;

	/// Log (message) severity.
	Severity_t severity;

};


} /* namespace logger */
} /* namespace mic */


#endif /* SCOPELOGGER_HPP_ */
