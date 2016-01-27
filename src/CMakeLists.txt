# Check compiler flags
include(CheckCXXCompilerFlag)

# Include current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# =======================================================================
# Add CMAKE variables.
# =======================================================================

set(BUILD_TEST_LOGGER ON CACHE BOOL "Build the application for testing logger")


# =======================================================================
# Build MI CORE libraries.
# =======================================================================

# =======================================================================
# Install includes related to SYSTEM UTILS used by other libraries.
FILE(GLOB files system_utils/*.hpp)
install(FILES ${files} DESTINATION include/system_utils)
  
# Create shared library containing SYSTEM UTILS used by all other libraries. DEPRICATED.
file(GLOB system_utils_src system_utils/*.cpp)
add_library(system_utils SHARED ${system_utils_src})


# =======================================================================
# Install includes related to LOGGER used by other libraries.
FILE(GLOB files logger/*.hpp)
install(FILES ${files} DESTINATION include/logger)
  
# Create shared library containing LOGGER used by all other libraries.
file(GLOB logger_src logger/*.cpp)
add_library(logger SHARED ${logger_src})
target_link_libraries(logger ${Boost_LIBRARIES} )



# =======================================================================
# Install includes related to CONFIGURATION used by other libraries.
FILE(GLOB files configuration/*.hpp)
install(FILES ${files} DESTINATION include/configuration)
  
# Create shared library containing CONFIGURATION used by all other libraries.
file(GLOB configuration_src configuration/*.cpp)
add_library(configuration SHARED ${configuration_src})
target_link_libraries(configuration ${Boost_LIBRARIES} logger)



# =======================================================================
# Install includes related to APPLICATION used by other libraries.
FILE(GLOB files application/*.hpp)
install(FILES ${files} DESTINATION include/application)
  
# Create shared library containing APPLICATION used by all other libraries.
file(GLOB application_src application/*.cpp)
add_library(application SHARED ${application_src})
target_link_libraries(application ${Boost_LIBRARIES} logger configuration)



# =======================================================================
# Install target libraries.
# =======================================================================

install(TARGETS system_utils logger configuration application LIBRARY DESTINATION lib)


# =======================================================================
# Build and install - logger test application.
# =======================================================================

if(${BUILD_TEST_LOGGER})
	# Create exeutable.
	ADD_EXECUTABLE(logger_test tests/logger_test.cpp)
	# Link it with shared libraries.
	target_link_libraries(logger_test 
		configuration
		logger
		${Boost_LIBRARIES}
		)

	# install test to bin directory
	install(TARGETS logger_test RUNTIME DESTINATION bin)

endif(${BUILD_TEST_LOGGER})
