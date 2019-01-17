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
 * \file Logger.hpp
 * \brief Contains declaration of a logger, a singleton responsible for logging and displaying all kinds of messages.
 * \author tkornuta
 * \date Dec 1, 2015
 */

#ifndef SRC_CONFIGURATION_LOGGER_HPP_
#define SRC_CONFIGURATION_LOGGER_HPP_

#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/ptr_container/ptr_vector.hpp>


#include <logger/LoggerOutput.hpp>


namespace mic {

/*!
 * \namespace mic::logger
 * \brief Contains classes, types and defines used for dynamic, multilevel logging.
 * \author tkornuta
 */
namespace logger {

/*!
 * \brief Logger - defined in the form of a singleton, with double-checked locking pattern (DCLP) based access to instance.
 * \author tkornuta
 */
class Logger {
public:
	/*!
	 * Method for accessing the object instance, with double-checked locking optimization.
	 * @return Instance of ApplicationState singleton.
	 */
	static Logger* getInstance();

	/*!
	 * Logs the message - sends it to registered logger outputs.
	 */
	void log(const std::string & file, int line, Severity_t sev, const std::string & msg);

	/*!
	 * Adds logger output.
	 */
	void addOutput(LoggerOutput * out);

	/*!
	 * Increments severity level.
	 */
	void incrementSeverityLevel();

	/*!
	 * Decrements severity level.
	 */
	void decrementSeverityLevel();


	/*!
	 * Set severity level.
	 */
	void setSeverityLevel(Severity_t sev);


private:
    /*!
     * Private instance - accessed as atomic operation.
     */
	static boost::atomic<Logger*> instance_;

	/*!
	 * Mutex used for instantiation of the instance.
	 */
	static boost::mutex instantiation_mutex;

	/*!
	 * Private constructor.
	 */
	Logger();

	/*!
	 * List of outputs.
	 */
	boost::ptr_vector<LoggerOutput> outputs;

};


} /* namespace logger */
} /* namespace mic */

#endif /* SRC_CONFIGURATION_LOGGER_HPP_ */
