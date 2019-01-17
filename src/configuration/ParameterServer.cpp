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
 * \file ParameterServer.cpp
* \brief Contains declaration of parameter server class methods.
  * \author tkornuta
 * \date Jan 4, 2016
 */

#include <configuration/ParameterServer.hpp>

#include <boost/property_tree/json_parser.hpp>

namespace mic {
namespace configuration {

// Initialize application instance - as NULL.
boost::atomic<ParameterServer*> ParameterServer::instance_(NULL);

// Initilize mutex.
boost::mutex ParameterServer::instantiation_mutex;

using boost::property_tree::ptree;

namespace po = boost::program_options;
namespace pt = boost::property_tree;

template<class Ptree>
inline const Ptree & empty_ptree()
{
	static Ptree pt;
	return pt;
}

ParameterServer* ParameterServer::getInstance() {
	// Try to load the instance - first check.
	ParameterServer* tmp = instance_.load(boost::memory_order_consume);
	// If instance does not exist.
	if (!tmp) {
		// Enter critical section.
		boost::mutex::scoped_lock guard(instantiation_mutex);
		// Try to load the instance - second check.
		tmp = instance_.load(boost::memory_order_consume);
		// If still does not exist - create new instance.
		if (!tmp) {
			tmp = new ParameterServer;
			instance_.store(tmp, boost::memory_order_release);
		}//: if
		// Exit critical section.
	}//: if
	// Return instance.
	return tmp;
}

ParameterServer::ParameterServer()
: program_options("Allowed options") 
{
	// TODO Auto-generated constructor stub
}

void ParameterServer::print(boost::property_tree::ptree const& pt_)
{
    LOG(LDEBUG)<< "Properties loaded from config file (raw):";
    for (ptree::const_iterator it = pt_.begin(); it != pt_.end(); ++it) {
    	LOG(LDEBUG) <<it->first << ": " << it->second.get_value<std::string>() << std::endl;
        print(it->second);
    }
}


const boost::property_tree::ptree & ParameterServer::returnNode(std::string node_name_)
{
	// Try to find the node.
    for (ptree::const_iterator it = config_tree.begin(); it != config_tree.end(); ++it) {
    	if (it->first == node_name_) {
    	    LOG(LINFO)<< "Node \"" << node_name_ << "\" has been found in config file";
    		return it->second;
    	}//: if
    }//: for

    // Return empty ptree otherwise.
    LOG(LWARNING)<< "Node " << node_name_ << " not found in config file";
    return empty_ptree<ptree>();
}


void ParameterServer::parseApplicationParameters(int argc, char* argv[]) {
	// Extract application (binary file) name.
	std::string tmp = std::string(argv[0]);
	application_name = tmp.substr(tmp.find_last_of("/\\")+1);

	// Config filenames.
	std::string default_config_name = application_name + ".json";

	std::string existing_config_name;

	std::string new_config_name = application_name + ".json";

	// Logger level.
	int log_lvl;

	// Declare the supported command-line options
	// NOTE: Program options are already created (in constructor) and may have been extended by applications.
	program_options.add_options()
		("help,h", "Display (h)elp message")
		("load-config,l", po::value<std::string>(&existing_config_name)->default_value(default_config_name.c_str()), "(L)oad configuration from given JSON file")
		("create-config,c", "(C)reate default configuration JSON file")
		("set-logger-level,s", po::value<int>(&log_lvl)->default_value(3), "(S)et logger severity level")
	;

	// Variables map.
	po::variables_map vm;

	// Try to parse the parameters.
	try {
		po::store(po::parse_command_line(argc, argv, program_options), vm);
		po::notify(vm);
	}
	catch (const po::error & u) {
		std::cout << u.what() << "\n";
		exit (0);
	}


	if (vm.count("help")) {
		std::cout << program_options << "\n";
		exit (0);
	}

	// Set logger severity level.
	LOGGER->setSeverityLevel((mic::logger::Severity_t)log_lvl);

	if (vm.count("create-config")) {
		std::cout << "Creating JSON file " << new_config_name << " with default configuration \n";

		std::ofstream cfg(new_config_name.c_str());

		cfg << "{\n"
				"	\"app_state\": {\n"
				"		\"application_sleep_interval\": \"1000\"\n"
				"	},\n"
				"	\"";
		cfg << 	std::string(argv[0]).erase(0,2);
		cfg <<	"\": {\n"
				"		\"learning_iterations_to_test_ratio\": \"50\",\n"
				"		\"number_of_averaged_test_measures\": \"5\"\n"
				"	}\n"
				"}";

		cfg.close();

		exit (0);
	}//: create config

	try {
		read_json(existing_config_name, config_tree);

		// Debug print config tree.
		LOG(LSTATUS) << "Configuration file \"" << existing_config_name + "\" was loaded properly";
	    print(config_tree);

	}
	catch(boost::property_tree::json_parser_error&) {
		LOG(LERROR) << "Configuration file \"" << existing_config_name + "\" was not found or invalid";
		LOG(LINFO) << "Quick fixes:";
		LOG(LINFO) << "   specify config file name with -l switch";
		LOG(LINFO) << "   create default configuration using -c switch";

		exit (0);
	}//: catch

}


void ParameterServer::registerPropertyTree(mic::configuration::PropertyTree* pt_) {
	if (pt_ != NULL) {
		LOG(LDEBUG) <<"Registering property tree " << pt_->getNodeName();
		// Register the property tree. TODO: add checking whether another property with that name existed earlier...
		property_trees_registry[pt_->getNodeName()] = pt_;
	}//: if
}

void ParameterServer::loadPropertiesFromConfiguration() {
	// For each "main" node in the loaded configuration.
    for (boost::property_tree::ptree::const_iterator cfg_it = config_tree.begin(); cfg_it != config_tree.end(); ++cfg_it) {

    	// Find property tree with given id.
    	id_pt_it_t reg_it = property_trees_registry.find(cfg_it->first);
    	if (reg_it != property_trees_registry.end()) {
    		 reg_it->second->loadPropertiesFromConfigNode(cfg_it->second);
    	} else {
    		LOG(LERROR) <<"Object \"" << cfg_it->first << "\" appearing in the loaded config file was not found in the property tree registry";
    	}//: else

    }//: for

    LOG(LINFO) << "Configuration completed";
	LOG(LSTATUS) << "List of application properties:";

	// For each registered property tree.
	for (id_pt_it_t reg_it = property_trees_registry.begin(); reg_it != property_trees_registry.end(); ++reg_it) {
		reg_it->second->printPropertiesWithValues();
	}//: for

	LOG(LINFO) << "Property-dependent variables initialized";
}

void ParameterServer::initializePropertyDependentVariables() {
    LOG(LSTATUS) << "Initializing property-dependent variables";

	// For each registered property tree.
    for (id_pt_it_t reg_it = property_trees_registry.begin(); reg_it != property_trees_registry.end(); ++reg_it) {

    	// Find property tree with given id.
    	reg_it->second->initializePropertyDependentVariables();

    }//: for

    LOG(LINFO) << "Property-dependent variables initialized";
}


boost::program_options::options_description &ParameterServer::getProgramOptions() {
	return program_options;
}

const boost::program_options::variables_map &ParameterServer::getProgramArguments() {
	return program_arguments;
}

} /* namespace configuration */
} /* namespace mic */
