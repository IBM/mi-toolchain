# Copyright (C) tkornuta, IBM Corporation 2015-2019
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Include current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# =======================================================================
# Build and install - logger test application.
# =======================================================================

set(BUILD_TEST_LOGGER ON CACHE BOOL "Build the application for testing logger")

if(${BUILD_TEST_LOGGER})
	# Create exeutable.
	ADD_EXECUTABLE(logger_test logger_test.cpp)
	# Link it with shared libraries.
	target_link_libraries(logger_test 
		configuration
		logger
		${Boost_LIBRARIES}
		)

	# install test to bin directory
	install(TARGETS logger_test RUNTIME DESTINATION bin)

endif(${BUILD_TEST_LOGGER})