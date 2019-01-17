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

# Include current directory BEFORE the others - this will result in using LOCAL headers before the ones pointed by the CMAKE_INSTALL_PREFIX path!
# Include in here will result in enabling to use global headers paths e.g. <opengl/visualization/Window.hpp>
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})


# =======================================================================
# Add subdirectories
# =======================================================================

add_subdirectory(logger)

add_subdirectory(configuration)

add_subdirectory(application)

add_subdirectory(test)

