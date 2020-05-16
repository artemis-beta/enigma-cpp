file(GLOB_RECURSE src_unit "*.cxx")

set(unit_tests ${PROJECT_NAME}-unit_tests)

add_executable(${unit_tests} ${src_unit})
add_compile_options(${unit_tests} ${BUILD_TYPE_COMPILE_FLAGS})

target_include_directories(${unit_tests} PRIVATE ${GTEST_INCLUDE_DIRS})
target_include_directories(${unit_tests} PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(${unit_tests} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${unit_tests} PUBLIC ${CMAKE_SOURCE_DIR}/logging)

target_include_directories(${unit_tests} PRIVATE ${GMOCK_INCLUDE_DIRS})
target_link_libraries(${unit_tests} PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${unit_tests} PRIVATE Logger)
target_link_libraries(${unit_tests} PRIVATE Enigma)
target_link_libraries(${unit_tests} PRIVATE ${PROJECT_LIBS} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

include(GoogleTest)
gtest_discover_tests(${unit_tests})