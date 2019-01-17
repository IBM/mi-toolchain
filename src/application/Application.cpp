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
 * \file Application.cpp
 * \brief Contains definition of methods of the base Application class.
 * \author tkornut
 * \date Dec 30, 2015
 */

#include <application/Application.hpp>

namespace mic {
namespace application {

Application::Application(std::string node_name_) : PropertyTree(node_name_),
	number_of_iterations("number_of_iterations",0)
{
	// Register properties.
	registerProperty(number_of_iterations);

	// Reset iteration counter.
	iteration = 0;

	// Register application in APP_STATE.
	APP_STATE->setApplication(this);
}


void Application::displayStatus() {
	// Iteration number.
	LOG(LSTATUS) << "Iteration:\t\t" << iteration;
}


void Application::run() {

 	// Main application loop.
	while (!APP_STATE->Quit()) {

		// If not paused.
		if (!APP_STATE->isPaused()) {
			// If single step mode - pause after the step.
			if (APP_STATE->isSingleStepModeOn())
				APP_STATE->pressPause();

			// Enter critical section - with the use of scoped lock from AppState!
			APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

			// Perform single step and - if required - break the loop.
			iteration++;
			if (!performSingleStep()) {
				LOG(LINFO) << "Terminating application...";
				APP_STATE->setQuit();
				break;
			} else if (((long)number_of_iterations > 0) && ( (long)iteration >= (long) number_of_iterations)) {
				LOG(LINFO) << "Reached last Iteration. Terminating application...";
				APP_STATE->setQuit();
				break;
			}//: else if

		} //: if! is paused & end of critical section

		// Sleep.
		APP_SLEEP();
	}//: while
}

} /* namespace application */
} /* namespace mic */
