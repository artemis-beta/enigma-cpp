cmake_minimum_required( VERSION 3.10 )
project( enigma_app VERSION 1.2.0 LANGUAGES CXX )

set(CMAKE_VERBOSE_MAKEFILE ON)
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )
set( SRCFILES src/Reflector.cxx src/Rotor.cxx src/Enigma.cxx )

find_package( Boost REQUIRED )

add_executable( ${PROJECT_NAME} ${SRCFILES} enigma_app.cxx )

add_subdirectory( logging )
target_link_libraries( ${PROJECT_NAME} PUBLIC Logger )
target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} ${LIBS} )
target_include_directories( ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include
                           ${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS}
                           ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/logging )