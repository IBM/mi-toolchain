# Project name
project(MIToolchain CXX)

#  Set current version number.
set (MIToolchain_MAJOR_VERSION 1)
set (MIToolchain_MINOR_VERSION 0)
set (MIToolchain_PATCH_VERSION 0)
set (MIToolchain_VERSION ${MIToolchain_MAJOR_VERSION}.${MIToolchain_MINOR_VERSION}.${MIToolchain_PATCH_VERSION})

# CMake required version.
cmake_minimum_required(VERSION 3.2)

# Add C++11 dependency.
if (WIN32)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall -Ic:/progra~1/boost/boost_1_60_0")
else ()
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall")
endif ()

# =======================================================================
# Find required packages
# =======================================================================

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Find boost package
find_package(Boost 1.54 REQUIRED COMPONENTS system thread random program_options regex date_time)
# Try to include Boost as system directory to suppress it's warnings
if (WIN32)
  include_directories(SYSTEM )
else ()
  include_directories(SYSTEM ${Boost_INCLUDE_DIR})
endif ()

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
# Create the cached variable for sstoring all library names.
set(MIToolchain_LIBRARIES "" CACHE INTERNAL "" FORCE)

# add subdirectory.
add_subdirectory(src)

message ("-- Configured MIToolchain libraries:\n" "--   " "${MIToolchain_LIBRARIES}")

# Set include directory
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/include")
# Set lib directory
set(CMAKE_LIB_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/lib")
# Set variable that will store generated libraries

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
  