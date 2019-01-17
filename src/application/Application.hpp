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
 * \file Application.hpp
 * \brief Contains declaration of a base class for all applications.
 * \author tkornuta
 * \date Dec 30, 2015
 */

#ifndef SRC_CONFIGURATION_APPLICATION_HPP_
#define SRC_CONFIGURATION_APPLICATION_HPP_

#include <application/ApplicationFactory.hpp>

#include <logger/Log.hpp>
using namespace mic::logger;

namespace mic {
namespace application {

/*!
 * \brief Base class for all applications.
 * \author tkornuta
 */
class Application : public configuration::PropertyTree {
public:
	/*!
	 * Constructor. Passess the node name to property tree.
	 */
	Application(std::string node_name_);


	/*!
	 * Virtual destructor. Empty for now.
	 */
	virtual ~Application() { };


	/*!
	 * Initializes application - abstract, must be implemented by a child class/application.
	 * @param argc Number of application parameters.
	 * @param argv Array of application parameters.
	 */
	virtual void initialize(int argc, char* argv[]) = 0;

	/*!
	 * Runs the application - virtual, can be overridden by a child class/application.
	 */
	virtual void run();

	/*!
	 * Displays application status.
	 */
	virtual void displayStatus();

protected:

	/// Iteration counter.
	unsigned long iteration;

	/*!
	 * Property: number of episodes, after which the application will end. 0 (default value) deactivates terminal condition (unlimited number of episodes).
	 */
	mic::configuration::Property<long> number_of_iterations;

	/*!
	 * Performs single step of computations - abstract, to be overridden.
	 */
	virtual bool performSingleStep() = 0;

};


} /* namespace application */
} /* namespace mic */

#endif /* SRC_CONFIGURATION_APPLICATION_HPP_ */
