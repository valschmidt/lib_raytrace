# \file CMakeLists.txt
# \brief Configuration file for examples

cmake_minimum_required( VERSION 3.0.0 )

project(main)

set( SRC 	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
		)

# pair executable and source files
add_executable( main ${HDR} ${SRC} )

# again just creating variables
set( TARGET_NAME 		"main" )
set( TARGET_DEBUG_POSTFIX 	"_d" )

#targets are comprised of executables or libraries
set_target_properties( main	PROPERTIES  	POSITION_INDEPENDENT_CODE ON
                               	OUTPUT_NAME  	${TARGET_NAME}
                               	FOLDER 		"lib_raytrace/app"
                               	DEBUG_POSTFIX 	${TARGET_DEBUG_POSTFIX}	
		      )

#linking the libraries together into the same 'place'
target_link_libraries( main	lib_raytrace )

#adding main
install( TARGETS	main	
	 DESTINATION 	"bin"	
	 COMPONENT 	raytrace_app 
	)

# DEBUG
#don't look at it too hard
#set( DEBUG_INST_DIR	"\${CMAKE_INSTALL_PREFIX}/app" )	
#set( DEBUG_APP	"${DEBUG_INST_DIR}/${TARGET_NAME}${TARGET_DEBUG_POSTFIX}$#{CMAKE_EXECUTABLE_SUFFIX}" )
#install( SCR 	"
#		if(\"\${CMAKE_INSTALL_CONFIG_NAME}\" STREQUAL \"Debug\")
#		include(BundleUtilities)
#		fixup_bundle( \"${DEBUG_APP}\" \"\" \"\")
#		endif()
#		"
#		COMPONENT raytrace_app 
#	)
