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
 * @file: PropertyTests.cpp
 * @Author: Tomasz Kornuta <tkornut@us.ibm.com>
 * @Date:   Jan 23, 2019
 */

#include <gtest/gtest.h>

#include <fstream>

// Redefine word "public" so every class field/method will be accessible for tests.
#define private public
#include <configuration/Property.hpp>

/*!
 * Tests whether assign operator works properly - for strings.
 */
TEST(Property, OperatorAssignString) {

	mic::configuration::Property<std::string> prop("string_property","empty_string");
	//std::cout<<"Setting value with operator=!\n";
	prop = "string";
	// std::cout<<"Getting value with ()\n";
	std::string s1 = prop;
	std::string s2 = "string";

	ASSERT_EQ(s1.size(), s2.size()) << "Strings s1 and s2 are of unequal length";

	for (int i = 0; i < s1.size(); ++i)
		EXPECT_EQ(s1[i], s2[i]) << "Strings s1 and s2 differ at index " << i;
}

/*!
 * Tests whether assign operator works properly - for int.
 */
TEST(Property, OperatorAssignInt) {

	mic::configuration::Property<int> prop("int_property",0);
	//std::cout<<"Setting value with operator=!\n";
	prop = 10;
	// std::cout<<"Getting value with ()\n";
	ASSERT_EQ(prop, 10) << "Property value not equal to value set(10)";

}


/*!
 * Tests whether assign operator works properly - for double.
 */
TEST(Property, OperatorAssignDouble) {

	mic::configuration::Property<double> prop("double_property",0);
	//std::cout<<"Setting value with operator=!\n";
	prop = 3.14;
	// std::cout<<"Getting value with ()\n";
	ASSERT_EQ(prop, 3.14) << "Property value not equal to value set(3.14)";

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


