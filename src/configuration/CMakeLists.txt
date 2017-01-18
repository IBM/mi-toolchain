# Include current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# =======================================================================
# Install includes related to CONFIGURATION used by other libraries.
# =======================================================================

FILE(GLOB files *.hpp)
install(FILES ${files} DESTINATION include/configuration)
  
# Create shared library containing CONFIGURATION used by all other libraries.
file(GLOB configuration_src *.cpp)
add_library(configuration SHARED ${configuration_src})
target_link_libraries(configuration ${Boost_LIBRARIES} logger)

# Add to variable storing all libraries/targets.
set(MIToolchain_LIBRARIES ${MIToolchain_LIBRARIES} "configuration" CACHE INTERNAL "" FORCE)

# Install target library.
install(TARGETS configuration LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
