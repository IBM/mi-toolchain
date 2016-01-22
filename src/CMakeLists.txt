# Check compiler flags
include(CheckCXXCompilerFlag)

# Include current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# =======================================================================
# Find Boost package
# =======================================================================
find_package(Boost 1.58 REQUIRED COMPONENTS system thread random program_options regex date_time)

# Try to include Boost as system directory to suppress it's warnings
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")



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

install(TARGETS system_utils logger configuration application LIBRARY DESTINATION lib)
#install(TARGETS  LIBRARY DESTINATION lib)
#install(TARGETS configuration LIBRARY DESTINATION lib)
#install(TARGETS application LIBRARY DESTINATION lib)



# =======================================================================
# Create variable containing all CORE libraries.
# =======================================================================
#SET(MIToolchain_LIBRARIES ${Boost_LIBRARIES} system_utils logger configuration application)
