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
