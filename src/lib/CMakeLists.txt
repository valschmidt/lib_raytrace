# \file CMakeLists.txt
# \brief Configuration file for library

cmake_minimum_required( VERSION 3.0.0 )

#project(lib_raytrace)

#setting header files
set( HDR 	${CMAKE_CURRENT_SOURCE_DIR}/data_ssp.h
		${CMAKE_CURRENT_SOURCE_DIR}/regular_ssp.h
		${CMAKE_CURRENT_SOURCE_DIR}/sparse_ssp.h
		${CMAKE_CURRENT_SOURCE_DIR}/ssp.h
		${CMAKE_CURRENT_SOURCE_DIR}/Stats.h
              	
#               ${CMAKE_CURRENT_BINARY_DIR}/art_API.h probably don't have to worry about this for now
                )



#setting .cpp files
set( SRC 	${CMAKE_CURRENT_SOURCE_DIR}/data_ssp.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/regular_ssp.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/sparse_ssp.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ssp.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Stats.cpp
                )


###____________________________________________________________________###
###                              Options                               ###

# Add -fvisibility=hidden to CMAKE_CXX_FLAGS where supported
#cmake doesn't recognize this command
#add_compiler_export_flags()

#why not include this directory, can't hurt
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

###____________________________________________________________________###
###                             Application                            ###

# Set sources, version and name for the shared library

#add_library & add_executable are basically the same thing
#we are in the lib folder so let's use add_library
#adding a library called "Template"

add_library( lib_raytrace	${LIB_TYPE}	${SRC}	${HDR} )

#again just creating variables
set( TARGET_NAME		"lib_raytrace" )
set( TARGET_DEBUG_POSTFIX	"_d" )

set_target_properties( 	lib_raytrace		
			PROPERTIES
		       	OUTPUT_NAME	${TARGET_NAME}
			FOLDER 		"lib_raytrace/lib"
                       	DEBUG_POSTFIX	${TARGET_DEBUG_POSTFIX}
                     )


#adding all the files to Template

install( TARGETS	lib_raytrace
	 DESTINATION	"lib/release"
	 CONFIGURATIONS	Release
	 COMPONENT	raytrace_lib
	)

install( TARGETS	lib_raytrace		                    
	 DESTINATION    "lib/debug" 		
         CONFIGURATIONS Debug	    
	 COMPONENT	raytrace_lib 
	)

install( FILES		${HDR}
	 DESTINATION	"lib/include"
         COMPONENT 	raytrace_lib 
	)

#install( FILES		${SRC}
#	 DESTINATION	"lib/include"
#        COMPONENT 	raytrace_lib 
#	)

#install( FILES		${CMAKE_CURRENT_BINARY_DIR}/RayTrace_API.h
#	  DESTINATION 	"lib/include" 	
#         COMPONENT 	raytrace_lib
#	)
                                                                                        