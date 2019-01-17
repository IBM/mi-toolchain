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
 * \file TrainThenTestApplication.cpp
 * \brief Contains definition of methods of train-then-test base application class.
 * \author tkornuta
 * \date Jan 15, 2016
 */

#include <application/TrainThenTestApplication.hpp>

namespace mic {
namespace application {


TrainThenTestApplication::TrainThenTestApplication(std::string node_name_) : Application(node_name_)
{
	// Start from learning.
	APP_STATE->setLearningModeOn();
}


void TrainThenTestApplication::run() {

	// Start from learning.
	APP_STATE->setLearningModeOn();

 	// Main application loop.
	while (!APP_STATE->Quit()) {

		// If not paused.
		if (!APP_STATE->isPaused()) {
			// If single step mode - pause after the step.
			if (APP_STATE->isSingleStepModeOn())
				APP_STATE->pressPause();

			// Enter critical section - with the use of scoped lock from AppState!
			APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

			// Increment iteration number - at START!
			iteration++;
			// Perform single step and - if required - break the loop.
			if (!performSingleStep())
				break;

		} //: if! is paused & end of critical section

		// Sleep.
		APP_SLEEP();
	}//: while
}

bool TrainThenTestApplication::performSingleStep(void) {
	// If learning mode.
	if (APP_STATE->isLearningModeOn())  {
		// Perform learning - until there is something to learn.
		if (!performLearningStep()) {
			APP_STATE->setLearningModeOff();
		}
	} else {
		// Perform testing - until there is something to test.
		if (!performTestingStep())
			return false;
	}//: else

	return true;
}




} /* namespace application */
} /* namespace mic */
