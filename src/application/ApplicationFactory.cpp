/*!
 * \file ApplicationFactory.cpp
 * \brief 
 * \author tkornut
 * \date Jan 7, 2016
 */

#include <application/ApplicationFactory.hpp>

namespace mic {
namespace application {

// Init application instance - as NULL.
boost::atomic<ApplicationFactory*> ApplicationFactory::instance_(NULL);

// Initilize mutex.
boost::mutex ApplicationFactory::instantiation_mutex;



ApplicationFactory* ApplicationFactory::getInstance() {
	// Try to load the instance - first check.
	ApplicationFactory* tmp = instance_.load(boost::memory_order_consume);
	// If instance does not exist.
	if (!tmp) {
		// Enter critical section.
		boost::mutex::scoped_lock guard(instantiation_mutex);
		// Try to load the instance - second check.
		tmp = instance_.load(boost::memory_order_consume);
		// If still does not exist - create new instance.
		if (!tmp) {
			tmp = new ApplicationFactory;
			instance_.store(tmp, boost::memory_order_release);
		}//: if
		// Exit critical section.
	}//: if
	// Return instance.
	return tmp;
}


ApplicationFactory::ApplicationFactory() {
	// NULL pointer - important!
	internal_factory = nullptr;
}

ApplicationFactory::~ApplicationFactory() {
	// TODO Auto-generated destructor stub
}

} /* namespace application */
} /* namespace mic */
