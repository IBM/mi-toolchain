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
 * \file ContinuousLearningApplication.cpp
 * \brief Contains definition of methods of continuous learning base application type.
 * \author tkornut
 * \date Jan 15, 2016
 */

#include <application/ContinuousLearningApplication.hpp>
#ifdef _WIN32
#include <system_utils/windows_extras.hpp>
#endif

namespace mic {
namespace application {

ContinuousLearningApplication::ContinuousLearningApplication(std::string node_name_) : Application(node_name_),
		learning_iterations_to_test_ratio("learning_iterations_to_test_ratio", 50),
		number_of_averaged_test_measures("number_of_averaged_test_measures", 5)
{
	// Register properties - so their values can be overridden (read from the configuration file).
	registerProperty(learning_iterations_to_test_ratio);
	registerProperty(number_of_averaged_test_measures);

	// Reset learning iteration counter.
	learning_iteration = 0;
}

void ContinuousLearningApplication::run() {

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

bool ContinuousLearningApplication::performSingleStep(void) {
	// Check the iteration number and settings.
	// If learning is on AND (NOT equal to learning_iterations_to_test_ratio) - learn!
	if (((iteration % learning_iterations_to_test_ratio) != 0) && APP_STATE->isLearningModeOn()) {
		// Perform learning.
		 return performLearningStep();
	} else { // Else - test
		// Perform testing.
		return performTestingStep();
	}//: else
}

bool ContinuousLearningApplication::performTestingStep() {
	// Increment iteration number - at START!
	learning_iteration++;

	LOG(LDEBUG) << "iteration=" << iteration << "learning_iteration=" << learning_iteration << " learning_iteration % number_of_averaged_test_measures =" << learning_iteration % number_of_averaged_test_measures;

	// Perform testing - two phases.
	collectTestStatistics();

	// If a given number of measures were collected - average them and populate (i.e. visualize).
	if (learning_iteration % number_of_averaged_test_measures == 0) {

		populateTestStatistics();
		// Reset learning iteration counter.
		learning_iteration=0;
	}//: if iteration

	return true;
} //: if test mode (!learning)


} /* namespace application */
} /* namespace mic */
