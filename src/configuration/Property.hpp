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
 * \file Property.hpp
 * \brief Contains declaration of the Property class.
 * \author tkornuta
 * \date Jan 4, 2016
 */

#ifndef SRC_CONFIGURATION_PROPERTY_HPP_
#define SRC_CONFIGURATION_PROPERTY_HPP_

#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>

#include <boost/preprocessor/list.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>

#include <typeinfo>
#include <map>
#include <sstream>

#include <iostream>

/*!
 * \namespace mic
 * \brief Main Machine Intelligence Core namespace.
 * \author tkornuta
 */
namespace mic {

/*!
 * \namespace mic::configuration
 * \brief Contains classes, types and types related to system configuration and management.
 * \author tkornuta
 */
namespace configuration {

/*!
 * \brief Template class used for lexical casting between string and other types. Used by Property class.
 * \author tkornuta
 */
template<typename T>
class LexicalTranslator {
public:
	static std::string toStr(const T & val) {
		try {
			return boost::lexical_cast<std::string>(val);
		} catch(...) {
			std::stringstream ss;
			ss << val;
			return ss.str();
		}
		return "";
	}

	static T fromStr(const std::string & str) {
		try {
			return boost::lexical_cast<T>(str);
		} catch (...) {
			std::stringstream ss(str);
			T ret;
			ss >> ret;
			return ret;
		}
		return T();
	}
};


/*!
 * \brief Basic interface property - used during registration etc.
 * \author tkornuta
 */
class PropertyInterface {
public:

	PropertyInterface(const std::string & name_) :
		property_name(name_) {
	}

	virtual ~PropertyInterface() {}

	/*!
	 * Returns property name.
	 * @return Name.
	 */
	const std::string & name() const {
		return property_name;
	}

	/*!
	 * Abstract method for retrieving the value of property from a string, defined in concrete property.
	 * @param str String from which value will be retrieved.
	 */
	virtual void setValue(const std::string & str) = 0;

	/*!
	 * Abstract method for returning the string representing the current value.
	 *
	 * @return string representation of current value.
	 */
	virtual std::string getValue() = 0;

private:
	/// Name of the property.
	std::string property_name;

};



/*!
 * \brief Template class for storing properties.
 * \author tkornuta
 */
template<class T, class Translator = LexicalTranslator<T> >
class Property : public PropertyInterface {
public:
	/*!
	 * Default constructor, sets name, type and sets value (calls default type constructor).
	 * @param name
	 * @param initializer
	 * @param type
	 */
	Property(const std::string& name_, const T & initializer_ = T(),
			std::string type_ = typeid(T).name()) : PropertyInterface(name_),
			property_value(initializer_), property_type(type_) {
	}

	/*!
	 * Access the data with function call syntax.
	 */
	T operator()() const {
		return property_value;
	}

	/*!
	 * Sets new value (with operator ()) and returns current value.
	 * @param New value
	 * @return Current value
	 */
	T operator()(T const & value_) {
		property_value = value_;
		return property_value;
	}

	/*!
	 * Returns property value.
	 * @return Current value
	 */
	operator T() const {
		return property_value;
	}

	/*!
	 * Sets new property value.
	 * @param value_ New value to be set.
	 * @return Current value
	 */
	T operator=(T const & value_) {
		property_value = value_;
		return property_value;
	}

	/*!
	 * Compares the value of the property with given value.
	 * @param value_ Compared value
	 * @return True is equal.
	 */
	bool operator==(T const & value_) {
		return property_value == value_;
	}

	/*!
	 * Compares the value of the property with a given value.
	 * @param value Compared value.
	 * @return True is different.
	 */
	bool operator!=(T const & value_) {
		return property_value != value_;
	}


	/*!
	 * Sets value on a basis of a string (with the use of translator).
	 * @param str String to retrieve value from.
	 */
	virtual void setValue(const std::string & str) {
		property_value = Translator::fromStr(str);
	}

	/*!
	 * Returns the string representing the current value.
	 *
	 * @return string representation of current value.
	 */
	virtual std::string getValue() {
		return Translator::toStr(property_value);
	}

	/*!
	 * Returns property type.
	 * @return Type.
	 */
	std::string type() const {
		return property_type;
	}


	/*!
	 * Overloaded stream operator.
	 * @param os Stream
	 * @param prop
	 * @return Property.
	 */
	friend std::ostream & operator<<(std::ostream & os, const Property & prop) {
		os << prop.property_value;
		return os;
	}

protected:
	/// Actual property value.
	T property_value;

	/// Type of the property
	std::string property_type;

};


/*!
 * \brief Type representing a pair consisting of name-property.
 * \author tkornuta
 */
typedef std::pair<std::string, PropertyInterface *> PropertyPair;

} /* namespace configuration */
} /* namespace mic */



#endif /* SRC_CONFIGURATION_PROPERTY_HPP_ */
