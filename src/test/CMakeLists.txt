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