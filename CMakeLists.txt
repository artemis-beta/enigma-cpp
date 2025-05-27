cmake_minimum_required( VERSION 3.20 )

set( ENIGMA EnigmaCLI )
set( ENIGMA_VERSION 2.0.0 )
set( ENIGMA_LIBRARY enigma )

project( ${ENIGMA} VERSION ${ENIGMA_VERSION} LANGUAGES CXX )

set( BETA 0 )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
file( GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx )
set( CMAKE_THREAD_LIBS_INIT "-lpthread" )
option( ENIGMA_BUILD_TESTS "Build Tests" OFF )
option( CODE_COVERAGE "Enable Coverage" OFF )

if( ENIGMA_BUILD_TESTS )
    message( STATUS "Will build unit tests" )
endif( ENIGMA_BUILD_TESTS )

if( CODE_COVERAGE )
    set( ENIGMA_BUILD_TESTS ON )
    message( STATUS "Including Code Coverage" )
    set( COVERAGE_COMPILER_FLAGS "-g -fprofile-arcs -ftest-coverage" )
    set( CMAKE_CXX_FLAGS "-Wall -Wextra ${COVERAGE_COMPILER_FLAGS} ${CMAKE_CXX_FLAGS}" )
endif()

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVERSION=\\\"${PROJECT_VERSION}\\\" -DBETA=${BETA} " )

set( SPDLOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog/include )

add_subdirectory( external/spdlog )

add_library( ${ENIGMA_LIBRARY} ${SRC_FILES} )
target_link_libraries( ${ENIGMA_LIBRARY} PUBLIC ${SPDLOG} )
target_include_directories( ${ENIGMA_LIBRARY} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_include_directories( ${ENIGMA_LIBRARY} PUBLIC ${SPDLOG_INCLUDE_DIR} )

# Expose headers for Enigma library to other targets
target_include_directories( ${ENIGMA_LIBRARY} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if( ENIGMA_BUILD_TESTS)
    add_subdirectory( tests )
endif()
add_subdirectory( applications )

if( CODE_COVERAGE )
    find_program( LCOV_PATH  NAMES lcov lcov.bat lcov.exe lcov.perl )
    find_program( GENHTML_PATH NAMES genhtml genhtml.perl genhtml.bat )
    find_program( GCOV_PATH gcov )
    
    set( LCOV_EXCLUDES "build/*" "/usr*" "tests/*")

    add_custom_target( coverage

        # Cleanup lcov
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -directory . -b ${CMAKE_CURRENT_SOURCE_DIR} --zerocounters

        # Create baseline to make sure untouched files show up in the report
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -c -i -d . -b ${CMAKE_CURRENT_SOURCE_DIR} -o ${ENIGMA_LIBRARY}.base

        # Run executables
        COMMAND ${CMAKE_SOURCE_DIR}/tests/bin/Enigma-unit_tests

        # Capturing lcov counters and generating report
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} --directory . -b ${CMAKE_CURRENT_SOURCE_DIR} --capture --output-file ${ENIGMA_LIBRARY}.capture

        # add baseline counters
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -a ${ENIGMA_LIBRARY}.base -a ${ENIGMA_LIBRARY}.capture --output-file ${ENIGMA_LIBRARY}.total

        # filter collected data to final coverage report and merge outputs
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} --remove ${ENIGMA_LIBRARY}.total ${LCOV_EXCLUDES} --output-file ${ENIGMA_LIBRARY}.info

        # Generate HTML output

        COMMAND ${GENHTML_PATH} -o ${ENIGMA_LIBRARY}_coverage ${ENIGMA_LIBRARY}.info

        # Set output files as GENERATED (will be removed on 'make clean')
        BYPRODUCTS
            ${ENIGMA_LIBRARY}.base
            ${ENIGMA_LIBRARY}.capture
            ${ENIGMA_LIBRARY}.total
            ${ENIGMA_LIBRARY}.info
            ${ENIGMA_LIBRARY}  # report directory

        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM # Protect arguments to commands
        COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
    )
endif( CODE_COVERAGE )
