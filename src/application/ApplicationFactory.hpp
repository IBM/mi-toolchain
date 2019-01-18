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
 * \file ApplicationFactory.hpp
 * \brief Contains declaration of application factory, used by common main files for initialization of application objects.
 * \author tkornuta
 * \date Jan 7, 2016
 */

#ifndef SRC_CONFIGURATION_APPLICATIONFACTORY_HPP_
#define SRC_CONFIGURATION_APPLICATIONFACTORY_HPP_

#include <map>          // for standard C++ library std::map class template
#include <string>       // for std::string
#include <utility>      // for std: :pair etc.

#include <stdexcept>

#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>

//#include <application/Application.hpp>
#include <application/ApplicationState.hpp>

namespace mic {
namespace application {

// Forward declaration of a class Application.
class Application;

/*!
 * \brief Abstract class constituting interface for application factories.
 * \author tkornuta
 */
class FactoryInterface {
public:
	/*!
	 * Destructor. Empty.
	 */
    virtual ~FactoryInterface() {}

	/*!
	 * Method responsible for run time specified object creation - abstract, to be overridden.
	 * @param app_name_ Name of the application.
	 * @return Pointer to Application-derived object.
	 */
    virtual mic::application::Application * create(std::string app_name_) = 0;
};


/*!
 * \brief Template class used for generation of concrete object factories.
 * This enables that each application has an equivalent factory class that provides a Create virtual -
 * \author tkornuta
 * @tparam AppType Template parameter denoting the application type.
 */
template <class AppType>
class TemplateFactory  : public FactoryInterface {
public:
	/*!
	 * Method responsible for run time specified object creation.
	 * @param app_name_ Name of the application.
	 * @return Application of a given, template type.
	 */
	mic::application::Application * create(std::string app_name_) {
        return new AppType(app_name_);
    }

};


/*!
 * \brief Application factory, class responsible for generation of an application object.
 * Defined in the form of a singleton, with double-checked locking pattern (DCLP) based access to instance.
 * \author tkornuta
 */
class ApplicationFactory : public FactoryInterface {
public:
	/*!
	 * Destructor. Empty.
	 */
	virtual ~ApplicationFactory();

	/*!
	 * Method for accessing the object instance, with double-checked locking optimization.
	 * @return Instance of ApplicationState singleton.
	 */
	static ApplicationFactory* getInstance();

	/*!
	 * Template method responsible for registration of an "internal application factory".
	 * @tparam AppType Template parameter denoting the application type.
	 */
	template <class AppType>
	void RegisterFactory()
	{
		if (internal_factory != nullptr)
			throw std::runtime_error("Application factory: internal factory already existing! Possible reason: multiple REGISTER_APPLICATION macro calls.");
	   internal_factory = new TemplateFactory<AppType> ;
	}

	/*!
	 * Method responsible for run time specified object creation - calls internal factory to do this job.
	 * @param app_name_ Name of the application.
	 * @return Application of a given, template type.
	 */
	mic::application::Application * create(std::string app_name_) {
		if (internal_factory != nullptr)
			return internal_factory->create(app_name_);
		else
			throw std::runtime_error("Application factory: internal factory not existing! Possible reason: Macro REGISTER_APPLICATION was not called.");
   }

private:
    /*!
     * Private instance - accessed as atomic operation.
     */
	static boost::atomic<ApplicationFactory*> instance_;

	/*!
	 * Mutex used for instantiation of the instance.
	 */
	static boost::mutex instantiation_mutex;

	/*!
	 * Constructor. Sets internal factory pointer to null.
	 */
	ApplicationFactory();


	/// "Internal factory", responsible for returning of classes of different objects (applications).
	FactoryInterface* internal_factory;
};


/*!
 * \brief Macro returning application factory instance.
 * \author tkornuta
 */
#define APP_FACTORY mic::application::ApplicationFactory::getInstance()


/*!
 * \brief Macro for registering application type/factory.
 * \author tkornuta
 */
#define REGISTER_APPLICATION(AppType) APP_FACTORY->RegisterFactory<AppType>();


/*!
 * \brief Declaration of a function that must be defined in each application-derived class separately.
 * \author tkornuta
 */
void RegisterApplication (void);



} /* namespace application */
} /* namespace mic */

#endif /* SRC_CONFIGURATION_APPLICATIONFACTORY_HPP_ */
