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
