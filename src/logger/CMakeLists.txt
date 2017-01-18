# Include current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# =======================================================================
# Install includes related to LOGGER used by other libraries.
# =======================================================================

FILE(GLOB files *.hpp)
install(FILES ${files} DESTINATION include/logger)
  
# Create shared library containing LOGGER used by all other libraries.
file(GLOB logger_src *.cpp)
add_library(logger SHARED ${logger_src})
target_link_libraries(logger ${Boost_LIBRARIES} )

# Add to variable storing all libraries/targets.
set(MIToolchain_LIBRARIES ${MIToolchain_LIBRARIES} "logger" CACHE INTERNAL "" FORCE)

# Install target library.
install(TARGETS logger LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
