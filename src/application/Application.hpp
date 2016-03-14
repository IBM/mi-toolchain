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
	 * Runs the application - abstract, must be implemented by a child class/application.
	 */
	virtual void run() = 0;

	/*!
	 * Displays application status.
	 */
	virtual void displayStatus();

protected:

	/// Iteration counter.
	unsigned long iteration;

};


} /* namespace application */
} /* namespace mic */

#endif /* SRC_CONFIGURATION_APPLICATION_HPP_ */
