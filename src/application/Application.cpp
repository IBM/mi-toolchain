/*!
 * \file Application.cpp
 * \brief 
 * \author tkornut
 * \date Dec 30, 2015
 */

#include <application/Application.hpp>

namespace mic {
namespace application {

Application::Application(std::string node_name_) : PropertyTree(node_name_)
{

	// Reset iteration counter.
	iteration = 0;

	// Register application in APP_STATE.
	APP_STATE->setApplication(this);
}


void Application::displayStatus() {
	// Iteration number.
	LOG(LSTATUS) << "Iteration:\t\t" << iteration;
}

} /* namespace application */
} /* namespace mic */
