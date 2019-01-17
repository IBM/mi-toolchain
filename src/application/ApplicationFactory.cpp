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
 * \file ApplicationFactory.cpp
 * \brief Contains definition of application factory methods.
 * \author tkornuta
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
