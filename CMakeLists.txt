# Project name
project(MIToolchain CXX)

# CMake required version.
cmake_minimum_required(VERSION 3.2)

# Add C++11 dependency.
add_definitions(-std=gnu++0x)

add_subdirectory(src)

# =======================================================================
# MIToolchainConfig.cmake preparation
# =======================================================================

#  Current version number:
set(MIToolchain_VERSION "1.0.0")

string(REGEX MATCHALL "[0-9]" MIToolchain_VERSION_PARTS "${MIToolchain_VERSION}")
list(GET MIToolchain_VERSION_PARTS 0 MIToolchain_VERSION_MAJOR)
list(GET MIToolchain_VERSION_PARTS 1 MIToolchain_VERSION_MINOR)
list(GET MIToolchain_VERSION_PARTS 2 MIToolchain_VERSION_PATCH)

# include directories
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE 
	"${CMAKE_INSTALL_PREFIX}/include/system_utils" 
	"${CMAKE_INSTALL_PREFIX}/include/configuration" 
	"${CMAKE_INSTALL_PREFIX}/include"
)

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
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MIToolchain - Machine Intelligence Core")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
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
