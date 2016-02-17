/*!
 * \file Application.hpp
 * \brief 
 * \author tkornut
 * \date Dec 30, 2015
 */

#ifndef SRC_CONFIGURATION_APPLICATION_HPP_
#define SRC_CONFIGURATION_APPLICATION_HPP_

#include <string>

#include <configuration/PropertyTree.hpp>

#include <application/ApplicationState.hpp>

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


/*!
 * \brief Declaration of a function that must be defined in each application-derived class separately.
 * \author tkornuta
 */
void RegisterApplication (void);


} /* namespace application */
} /* namespace mic */

#endif /* SRC_CONFIGURATION_APPLICATION_HPP_ */
