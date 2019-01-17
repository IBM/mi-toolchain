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
 * \file ContinuousLearningApplication.hpp
 * \brief Contains declaration of a base class for all continuous learning type applications.
 * \author tkornuta
 * \date Jan 15, 2016
 */

#ifndef SRC_OPENGL_APPLICATION_CONTINUOUSLEARNINGAPPLICATION_HPP_
#define SRC_OPENGL_APPLICATION_CONTINUOUSLEARNINGAPPLICATION_HPP_

#include <application/Application.hpp>

namespace mic {
namespace application {

/*!
 * \brief Parent class for all applications basing on continuous learning.
 * By default all computations are made within a single thread.
 *
 * \author tkornuta
 * \date Feb 17, 2016
 */
class ContinuousLearningApplication : public mic::application::Application {
public:

	/*!
	 * Default constructor. Sets the application/node name and registers properties.
	 * @param node_name_ Name of the application/node (in configuration file).
	 */
	ContinuousLearningApplication(std::string node_name_);

	/*!
	 * Default destructor - empty.
	 */
	virtual ~ContinuousLearningApplication() { };

	/*!
	 * Handles pause/single step/quit modes/orders, calls performSingleStep() on every step.
	 */
	void run();

protected:

	/*!
	 * \brief Performs single step of computations - switches between learning and testing depending on the iteration number.
	 */
	virtual bool performSingleStep(void);

	/*!
	 * Perform learning - abstract, to be overridden.
	 */
	virtual bool performLearningStep() = 0;

	/*!
	 * Testing is divided into two phases: collection of test statistics and their population.
	 * The former is executed in every testing step, whereas the latter only every number_of_averaged_test_measures testing steps.
	 */
	virtual bool performTestingStep();

	/*!
	 * Collects test statistics, executed in every testing step - virtual, empty now, to be overridden.
	 */
	virtual void collectTestStatistics() { };

	/*!
	 * Populates test statistics, executed only every number_of_averaged_test_measures testing steps - virtual, empty now, to be overridden.
	 */
	virtual void populateTestStatistics() { };

	/// Number of learning steps after which a single classification test will be performed.
	mic::configuration::Property<unsigned int> learning_iterations_to_test_ratio;

	/// Numbers of steps that will be averages
	mic::configuration::Property<unsigned int> number_of_averaged_test_measures;

	/// Learning iteration counter - used in interlaces learning/testing mode.
	unsigned long learning_iteration;

};

} /* namespace application */
} /* namespace mic */

#endif /* SRC_OPENGL_APPLICATION_CONTINUOUSLEARNINGAPPLICATION_HPP_ */
