file( GLOB SRC_UNIT ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx )

set( UNIT_TESTS ${ENIGMA_LIBRARY}-unit-tests )

add_executable( ${UNIT_TESTS} ${SRC_UNIT} )
add_compile_options( ${UNIT_TESTS} ${BUILD_TYPE_COMPILE_FLAGS} )

target_include_directories( ${UNIT_TESTS} PUBLIC ${SPDLOG_INCLUDE_DIR} )

target_link_libraries( ${UNIT_TESTS} PUBLIC gtest_main )
target_link_libraries( ${UNIT_TESTS} PUBLIC ${Boost_LIBRARIES} )
target_link_libraries( ${UNIT_TESTS} PUBLIC ${ENIGMA_LIBRARY} )

include( GoogleTest )
gtest_discover_tests( ${UNIT_TESTS} )