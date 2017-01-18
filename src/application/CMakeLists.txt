# Include current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# =======================================================================
# Install includes related to APPLICATION used by other libraries.
# =======================================================================

FILE(GLOB files *.hpp)
install(FILES ${files} DESTINATION include/application)
  
# Create shared library containing APPLICATION used by all other libraries.
file(GLOB application_src *.cpp)
add_library(application SHARED ${application_src})
target_link_libraries(application ${Boost_LIBRARIES} logger configuration)

# Add to variable storing all libraries/targets.
set(MIToolchain_LIBRARIES ${MIToolchain_LIBRARIES} "application" CACHE INTERNAL "" FORCE)

# Install target library.
install(TARGETS application LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)

