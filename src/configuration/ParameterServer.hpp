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
 * \file ParameterServer.hpp
 * \brief Contains declaration of parameter server singleton along with some auxiliary typedefs.
 * \author tkornuta
 * \date Jan 4, 2016
 */

#ifndef SRC_CONFIGURATION_PARAMETERSERVER_HPP_
#define SRC_CONFIGURATION_PARAMETERSERVER_HPP_

#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/program_options.hpp>

#include <logger/Log.hpp>
using namespace mic::logger;

#include <configuration/PropertyTree.hpp>


namespace mic {
namespace configuration {

/*!
 * \brief Type used in adding property trees to registry.
 * \author tkornuta
 */
typedef std::pair<std::string, mic::configuration::PropertyTree*> id_pt_pair_t;


/*!
 * \brief Type used during iterating/searching for property trees in registry.
 * \author tkornuta
 */
typedef std::map<std::string, mic::configuration::PropertyTree*>::iterator id_pt_it_t;



/*!
 * \brief Server of application parameters - defined in the form of a singleton, with double-checked locking pattern (DCLP) based access to instance.
 * \author tkornuta
 */
class ParameterServer {
public:
	/*!
	 * Method for accessing the object instance, with double-checked locking optimization.
	 * @return Instance of ApplicationState singleton.
	 */
	static ParameterServer* getInstance();

	/*!
	 * Prints the tree - a recursive function.
	 * @param pt A property tree object (config_tree as default).
	 */
	void print(boost::property_tree::ptree const& pt);

	/*!
	 * Returns property tree of a node of given name. Returns nullptr if not found.
	 * @param node_name_ Name of the node.
	 * @return Property tree of a found node, nullptr otherwise.
	 */
	const boost::property_tree::ptree & returnNode(std::string node_name_);


	/*!
	 * Adds the property tree to the registry.
	 * @param pt_ Pointer to the registered property tree object.
	 */
	void registerPropertyTree(mic::configuration::PropertyTree* pt_);


	/*!
	 * Returns program options.
	 */
	boost::program_options::options_description &getProgramOptions();

	/*!
	 * Returns program arguments.
	 */
	const boost::program_options::variables_map &getProgramArguments();

	/*!
	 * Method parses (and stores) the application parameters.
	 * @param argc Number of application parameters.
	 * @param argv Array of application parameters.
	 */
	void parseApplicationParameters(int argc, char* argv[]);

	/*!
	 * Loads the properties from configuration. For each main node of the loaded configuration file it tries to find the corresponding "registered property tree", and if succeed - loads its properties.
	 */
	void loadPropertiesFromConfiguration();

	/*!
	 * Initilizes variables of all registered property trees.
	 */
	void initializePropertyDependentVariables();


	/*!
	 * Returns number of application parameters.
	 */
	int getArgc() { return argc; }

	/*!
	 * Returns application parameters.
	 */
	char ** getArgv() {return argv; }

	/*!
	 * Returns application name.
	 */
	std::string getAppName() { return application_name; }

private:
    /*!
     * Private instance - accessed as atomic operation.
     */
	static boost::atomic<ParameterServer*> instance_;

	/*!
	 * Mutex used for instantiation of the instance.
	 */
	static boost::mutex instantiation_mutex;

	/*!
	 * Provate constructor.
	 */
	ParameterServer();

	//virtual ~ParameterServer();

	/*!
	 * Property tree.
	 */
    boost::property_tree::ptree config_tree;

    /*!
     * Program options, to parse command line arguments.
     * This gets populated by default with a few arguments (like "help") and applications
     * can add additional options by accessing this field via getProgramOptions()
     */
	boost::program_options::options_description program_options;


	/**!
	 * The program_arguments holds the actual command line arguments received.
	 * This variable takes value only after parseApplicationArguments().
	 * Note that before that call, an application may call getProgramOptions() and extend
	 * the set of allowed command line arguments with new command line options;
	 * then call getProgramArguments to obtain their actual values.
	 */
	boost::program_options::variables_map program_arguments;

    /*!
     * Vector of registered property trees.
     */
    std::map<std::string, mic::configuration::PropertyTree*> property_trees_registry;


	 /// Number of application parameters.
	 int argc;

	 /// Array of application parameters.
	 char** argv;

	 /// Name of the executed binary file.
	 std::string application_name;

};


/*!
 * \brief Macro returning parameter server instance.
 * \author tkornuta
 */
#define PARAM_SERVER mic::configuration::ParameterServer::getInstance()

} /* namespace configuration */
} /* namespace mic */

#endif /* SRC_CONFIGURATION_PARAMETERSERVER_HPP_ */
