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
 * \file TrainThenTestApplication.hpp
 * \brief Contains declaration of a base class for all train-then-test type applications.
 * \author tkornuta
 * \date Jan 15, 2016
 */

#ifndef SRC_OPENGL_APPLICATION_TRAINTHENTESTAPPLICATION_HPP_
#define SRC_OPENGL_APPLICATION_TRAINTHENTESTAPPLICATION_HPP_

#include <application/Application.hpp>

namespace mic {
namespace application {

/*!
 * \brief Parent class for all applications consisting of two phases: a training phase (first), and testing phase (second).
 * Each phase will end when then an adequate method (performLearning/TrainingStep) will return false.
 * By default all computations are made within a single thread.
 *
 * \author tkornuta
 * \date Feb 17, 2016
 */
class TrainThenTestApplication : public mic::application::Application {
public:
	/*!
	 * Default constructor. Sets the application/node name and registers properties.
	 * @param node_name_ Name of the application/node (in configuration file).
	 */
	TrainThenTestApplication(std::string node_name_);

	/*!
	 * Default destructor - empty.
	 */
	virtual ~TrainThenTestApplication() { };

	/*!
	 * Main application method - runs consecutive steps, first learning (in several steps, until performLearningStep() will return false) then testing (until performTestingStep() will return false, then finish).
	 */
	void run();


protected:
	/*!
	 * Performs single step of computations. Depending on the state, calls learning or testing step - switches from learning to testing then learning return false.
	 */
	virtual bool performSingleStep();

	/*!
	 * Perform learning step - abstract, to be overridden.
	 * @return Returns false when test learning is completed.
	 */
	virtual bool performLearningStep() = 0;

	/*!
	 * Perform testing step - abstract, to be overridden.
	 * @return Returns false when test learning is completed.
	 */
	virtual bool performTestingStep() = 0;

};

} /* namespace application */
} /* namespace mic */

#endif /* SRC_OPENGL_APPLICATION_TRAINTHENTESTAPPLICATION_HPP_ */
