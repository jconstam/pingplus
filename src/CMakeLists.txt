cmake_minimum_required( VERSION 3.5 )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror" )

project( ${MAIN_PROJECT_NAME} )

set( SOURCES
    ${PROJECT_SOURCE_DIR}/ping.cpp

    ${PROJECT_SOURCE_DIR}/main.cpp
)

include_directories(
	${PROJECT_SOURCE_DIR}/include
)

add_executable( 
    ${MAIN_PROJECT_NAME} 
    ${SOURCES}
)