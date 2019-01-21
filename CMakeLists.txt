# \file CMakeLists.txt
# \brief Top-level CMake configuration
# \author: Eric Keilty

#Version needed to run
cmake_minimum_required( VERSION 3.0.0 )




# including a bunch of installation stuff:

# Set the installation folder (default or user-defined)
#include( cmake/SetInstallationFolder.cmake )
# Set the configuration types (Debug and Release)
#include( cmake/SetConfigurationTypes.cmake )
# Provide the status operator
#include( cmake/UtilsStatus.cmake )
# Detect the building environment (e.g. setup the compiler)
#include( cmake/DetectEnvironment.cmake )
# Retrieve the project version
#include( cmake/GetProjectVersion.cmake )
# Set options
#include( cmake/SetOptions.cmake )




#declaring project name
#name it the name of the folder that this is inside of
project ( Template_project )




# Including directories
include_directories( 	${CMAKE_SOURCE_DIR}/src/lib
                       ${CMAKE_BINARY_DIR}/src/lib
			)

#include( cmake/ShowSummary.cmake )



#adding 'src' as a directory
add_subdirectory( src )
