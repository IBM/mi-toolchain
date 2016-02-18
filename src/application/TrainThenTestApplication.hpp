/*!
 * \file TrainThenTestApplication.hpp
 * \brief 
 * \author tkornut
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
