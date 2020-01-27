cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set( BOOST $ENV{BOOSTINCLUDE} )
set( CMAKE_GENERATOR ${CXX_LOC})
set( SRCFILES src/Reflector.cxx src/Rotor.cxx src/Enigma.cxx )

project(enigma_app)

add_subdirectory(logging)
add_executable(${PROJECT_NAME} ${SRCFILES} enigma_app.cxx)
target_link_libraries(${PROJECT_NAME} ${LIBS} )
add_library( logging STATIC IMPORTED )
set_target_properties(logging PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/logging/build/libLogger.a)
target_link_libraries(${PROJECT_NAME} logging)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include
                           ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/logging
                           ${PROJECT_NAME} PUBLIC ${BOOST})