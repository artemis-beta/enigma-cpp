cmake_minimum_required( VERSION 3.10 )
project( Enigma VERSION 1.2.0 LANGUAGES CXX )

set(CMAKE_VERBOSE_MAKEFILE ON)
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set( SRCFILES src/Reflector.cxx src/Rotor.cxx src/Enigma.cxx )

option(CODE_COVERAGE "Enable Coverage" OFF)

find_package( Boost REQUIRED )

add_library(${PROJECT_NAME} ${SRCFILES})

add_subdirectory( tests )
add_subdirectory( logging )
add_subdirectory( applications )

target_link_libraries( ${PROJECT_NAME} PUBLIC Logger )
target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} ${LIBS} )
target_include_directories( ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include
                            ${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS}
                            ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/logging )

if(CODE_COVERAGE)
message(STATUS "Including Code Coverage")
set(COVERAGE_COMPILER_FLAGS "-g -fprofile-arcs -ftest-coverage")
set (CMAKE_CXX_FLAGS "-std=gnu++11 -Wall -Wextra ${COVERAGE_COMPILER_FLAGS} ${CMAKE_CXX_FLAGS}")

find_program( LCOV_PATH  NAMES lcov lcov.bat lcov.exe lcov.perl)
find_program( GENHTML_PATH NAMES genhtml genhtml.perl genhtml.bat )
find_program( GCOV_PATH gcov )

set(LCOV_EXCLUDES "build/*" "/usr*" "tests/*")

    add_custom_target(coverage

        # Cleanup lcov
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -directory . -b ${PROJECT_SOURCE_DIR} --zerocounters

        # Create baseline to make sure untouched files show up in the report
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -c -i -d . -b ${PROJECT_SOURCE_DIR} -o ${PROJECT_NAME}.base

        # Run executables
        COMMAND ${CMAKE_SOURCE_DIR}/tests/bin/Enigma-unit_tests

        # Capturing lcov counters and generating report
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} --directory . -b ${PROJECT_SOURCE_DIR} --capture --output-file ${PROJECT_NAME}.capture

        # add baseline counters
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -a ${PROJECT_NAME}.base -a ${PROJECT_NAME}.capture --output-file ${PROJECT_NAME}.total

        # filter collected data to final coverage report and merge outputs
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} --remove ${PROJECT_NAME}.total ${LCOV_EXCLUDES} --output-file ${PROJECT_NAME}.info

        # Generate HTML output

        COMMAND ${GENHTML_PATH} -o ${PROJECT_NAME}_coverage ${PROJECT_NAME}.info

        # Set output files as GENERATED (will be removed on 'make clean')
        BYPRODUCTS
            ${PROJECT_NAME}.base
            ${PROJECT_NAME}.capture
            ${PROJECT_NAME}.total
            ${PROJECT_NAME}.info
            ${PROJECT_NAME}  # report directory

        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        VERBATIM # Protect arguments to commands
        COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
    )
endif(CODE_COVERAGE)