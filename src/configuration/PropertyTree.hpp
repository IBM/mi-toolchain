/*!
 * \file PropertyTree.hpp
 * \brief Contains declaration of the PropertyTree class.
 * \author tkornuta
 * \date Jan 4, 2016
 */

#ifndef SRC_CONFIGURATION_PROPERTYTREE_HPP_
#define SRC_CONFIGURATION_PROPERTYTREE_HPP_

#include <configuration/Property.hpp>

#include <boost/property_tree/ptree.hpp>

namespace mic {
namespace configuration {

/*!
 * \brief Parent class for all classes possessing properties. Contains methods useful for their management, configuration, displaying etc.
 * \author tkornuta
 */
class PropertyTree {
public:
	/*!
	 * Constructor. Sets the node name.
	 * @param node_name_ Name of the node (in configuration file).
	 */
	PropertyTree(std::string node_name_);

	/*!
	 * Virtual destructor. Empty now.
	 */
	virtual ~PropertyTree();

	/*!
	 * Registers property - so its values can be externally overridden (e.g. read from the configuration file).
	 * \param prop Registered property.
	 */
	void registerProperty(PropertyInterface & prop);

	/*!
	 * Returns node name.
	 * @return Node name.
	 */
	std::string getNodeName();

	/*!
	 * Reads the values of its properties from config node.
	 */
	void loadPropertiesFromConfigNode(boost::property_tree::ptree const& pt_);

	/*!
	 * Prints the list of all registered properties.
	 */
	void printProperties();

	/*!
	 * Prints the list of all registered properties along with their values.
	 */
	void printPropertiesWithValues();

	/*!
	 * Returns property with specified name if registered or NULL otherwise.
	 * \param name Property name.
	 * \returns Pointer to a property with specified name or NULL if no such a property is registered.
	 */
	PropertyInterface * getProperty(const std::string& name);

	/*!
	 * Method responsible for initialization of all variables that are property-dependent - to make sure that one i.e. allocates memory for a block of adequate size (that is loaded from the configuration file).
	 */
	virtual void initializePropertyDependentVariables() = 0;

private:
	/// Map of all registered properties.
	std::map<std::string, mic::configuration::PropertyInterface*> properties;

	/// Name of the node in configuration file.
	std::string node_name;
};

} /* namespace configuration */
} /* namespace mic */

#endif /* SRC_CONFIGURATION_PROPERTYTREE_HPP_ */
