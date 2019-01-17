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

# Project name
project(MIToolchain CXX C)

#  Set current version number.
set (MIToolchain_MAJOR_VERSION 1)
set (MIToolchain_MINOR_VERSION 1)
set (MIToolchain_PATCH_VERSION 0)
set (MIToolchain_VERSION ${MIToolchain_MAJOR_VERSION}.${MIToolchain_MINOR_VERSION}.${MIToolchain_PATCH_VERSION})

# CMake required version.
cmake_minimum_required(VERSION 2.8)

# =======================================================================
# Set compiler/linker flags.
# =======================================================================

# Add C++11 dependency.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -Wall")

# Check, whether all necessary libraries are linked
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ") 

# =======================================================================
# Find required packages
# =======================================================================
# Add path to cmake dir.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Find boost package
find_package(Boost 1.54 REQUIRED COMPONENTS system thread random program_options regex date_time)
# Try to include Boost as system directory to suppress it's warnings
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

# =======================================================================
# RPATH settings
# =======================================================================
# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# =======================================================================
# Cmake configuration
# =======================================================================
# Create the cached variable for storing all library names.
set(MIToolchain_LIBRARIES "" CACHE INTERNAL "" FORCE)

add_subdirectory(src)

# Set include directory
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/include ${CMAKE_ADD_INCLUDE_PATH}")
# Set lib directory
set(CMAKE_LIB_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/lib ${CMAKE_ADD_LIB_PATH}")
# Set variable that will store generated libraries

message ("-- Configured MI Toolchain libraries:\n" "--   " "${MIToolchain_LIBRARIES}")

# =======================================================================
# Preparation of cmake configs
# =======================================================================

# Configure *Config.cmake and *ConfigVersion.cmake
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/MIToolchainConfig.cmake.in" "${CMAKE_BINARY_DIR}/MIToolchainConfig.cmake" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/MIToolchainConfigVersion.cmake.in" "${CMAKE_BINARY_DIR}/MIToolchainConfigVersion.cmake" @ONLY)

# Install the *Config.cmake and *ConfigVersion.cmake
install(FILES
  "${CMAKE_BINARY_DIR}/MIToolchainConfig.cmake"
  "${CMAKE_BINARY_DIR}/MIToolchainConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/MIToolchain/")
  