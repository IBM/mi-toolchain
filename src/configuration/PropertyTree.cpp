/*!
 * \file PropertyTree.cpp
 * \brief 
 * \author tkornut
 * \date Jan 4, 2016
 */

#include <configuration/PropertyTree.hpp>

#include <configuration/ParameterServer.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace mic {
namespace configuration {


PropertyTree::PropertyTree(std::string node_name_) : node_name(node_name_) {
	// Register this property tree.
	PARAM_SERVER->registerPropertyTree(this);
}

PropertyTree::~PropertyTree() {
	// TODO Auto-generated destructor stub
}

std::string PropertyTree::getNodeName() {
	return node_name;
}


void PropertyTree::registerProperty(PropertyInterface & prop) {
	// Register the property. TODO: add checking whether another property with that name existed earlier...
	properties[prop.name()] = &prop;
}

void PropertyTree::printProperties() {
	// Check if there are any properties.
	if (properties.empty()){
		LOG(LDEBUG) << "Registered properties in object \""<< node_name << "\": empty";
		return;
	}//: if

	LOG(LDEBUG) << "Registered properties in object \""<< node_name << "\":";
	BOOST_FOREACH(PropertyPair prop, properties) {
		LOG(LDEBUG) << "\t" << prop.first;
	}//: foreach
}


PropertyInterface * PropertyTree::getProperty(const std::string& name) {
	if (properties.count(name) > 0) {
		return properties[name];
	} else {
		return NULL;
	}
}


void PropertyTree::loadPropertiesFromConfigNode(boost::property_tree::ptree const& pt_) {
	LOG(LTRACE) << "PropertyTree::loadPropertiesFromConfigNode";

	std::string name;
	std::string value;
	std::string key;

	// Iterate through all properties in config file.
    using boost::property_tree::ptree;
    for (ptree::const_iterator it = pt_.begin(); it != pt_.end(); ++it) {

		// Read name and value.
		name = it->first;
		value = it->second.get_value<std::string>();

		LOG(LDEBUG) << "Property: " << name << "=" << value;

		// Find adequte object property.
		mic::configuration::PropertyInterface * prop = getProperty(name);
		if (!prop) {
			LOG(LWARNING) << "Object \"" << node_name << "\" has no property named \"" << name << "\", which is defined in configuration file.";
			continue;
		}

		// Set value.
		prop->setValue(value);
		LOG(LINFO) << "Object \"" << node_name << "\": property \"" << prop->name() << "\" value set to " << prop->getValue();
	}

}

/*
BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("particles.electron"))
 {
//     assert(v.first.empty()); // array elements have no names
     std::cout << v.first.data() << std::endl;
     std::cout << v.second.data() << std::endl;
     // etc
 }
 */

} /* namespace configuration */
} /* namespace mic */
