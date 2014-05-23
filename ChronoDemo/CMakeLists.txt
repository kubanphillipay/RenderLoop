cmake_minimum_required (VERSION 2.6)


project (CMakeDemo)



if(MSVC_IDE)
	message( STATUS "Using visual studio i think" )
else()
	message( STATUS "Using GCC or something else compiler" )
	ADD_DEFINITIONS(
	    -std=c++11 # Or -std=c++0x
	    # Other flags
	)
endif()


file( GLOB CHRONO_SRC *.cpp ) 
file( GLOB CHRONO_HDR *.h ) 

add_executable(ProgramExe ${CHRONO_SRC} ${CHRONO_HDR} )
#target_link_libraries( DemoExe Library1 )

