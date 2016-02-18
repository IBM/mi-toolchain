# Project name
project(MIToolchain CXX)

#  Set current version number.
set (MIToolchain_VERSION_MAJOR 1)
set (MIToolchain_VERSION_MINOR 0)
set (MIToolchain_VERSION_PATCH 0)
set (MIToolchain_VERSION ${MIToolchain_VERSION_MAJOR}.${MIToolchain_VERSION_MINOR}.${MIToolchain_VERSION_PATCH})

# CMake required version.
cmake_minimum_required(VERSION 3.2)

# Add C++11 dependency.
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall")

# =======================================================================
# Find required packages
# =======================================================================

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Find boost package
find_package(Boost 1.58 REQUIRED COMPONENTS system thread random program_options regex date_time)
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

add_subdirectory(src)

# =======================================================================
# MIToolchainConfig.cmake preparation
# =======================================================================

# include directories
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/include")

# lib directory

set(CMAKE_LIB_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/lib")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/MIToolchainConfig.cmake.in" "${CMAKE_BINARY_DIR}/MIToolchainConfig.cmake" IMMEDIATE @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/MIToolchainConfig.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/share/MIToolchain/)

# =======================================================================
# CPack: binary installer generator
# =======================================================================

# CPack variables used when generating binary installer
set(CPACK_PACKAGE_NAME "MIToolchain")
set(CPACK_PACKAGE_VENDOR "MIToolchain")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MIToolchain - Machine Intelligence Toolchain")
set(CPACK_PACKAGE_VERSION ${MIToolchain_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${MIToolchain_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${MIToolchain_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${MIToolchain_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "MIToolchain")

# License file
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

# Tell CPack all of the components to install. The "ALL"
# refers to the fact that this is the set of components that
# will be included when CPack is instructed to put everything
# into the binary installer (the default behavior).
set(CPACK_COMPONENTS_ALL system_utils logger configuration application)

# This must always be last!
include(CPack)
