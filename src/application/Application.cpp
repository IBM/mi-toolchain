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
}



} /* namespace application */
} /* namespace mic */
