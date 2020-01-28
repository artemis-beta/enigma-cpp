cmake_minimum_required(VERSION 3.10)

set(HOME $ENV{HOME})
set(Qt5_DIR /usr/local/opt/qt5/lib/cmake/Qt5)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH /usr/local/opt/qt5/lib/cmake)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(BOOST $ENV{BOOSTINCLUDE})
set(MACOSX_BUNDLE_ICON_FILE enigma_icon.icns)
project(EnigmaUI)
set(ENIGMA_ICON ${CMAKE_CURRENT_SOURCE_DIR}/images/enigma_icon.icns)
set_source_files_properties(${ENIGMA_ICON} PROPERTIES
       MACOSX_PACKAGE_LOCATION "Resources")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_definitions(-DQT_DEPRECATED_WARNINGS)

qt5_wrap_cpp(UI_SRC ${PROJECT_SOURCE_DIR}/include/enigma_mainwindow.hxx ${PROJECT_SOURCE_DIR}/include/helpdialog.hxx)
qt5_wrap_ui(UI_HEADERS ${PROJECT_SOURCE_DIR}/src/enigma_mainwindow.ui ${PROJECT_SOURCE_DIR}/src/helpdialog.ui)

set(ENIGMA_FILES ${PROJECT_SOURCE_DIR}/src/Reflector.cxx ${PROJECT_SOURCE_DIR}/src/Rotor.cxx ${PROJECT_SOURCE_DIR}/src/Enigma.cxx)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${LOGGER_FILES} ${ENIGMA_FILES} ${PROJECT_SOURCE_DIR}/src/helpdialog.cxx ${PROJECT_SOURCE_DIR}/src/enigma_mainwindow.cxx ${PROJECT_SOURCE_DIR}/src/main.cxx ${UI_HEADERS} ${UI_SRC} ${ENIGMA_ICON} ${allSources})
target_link_libraries(${PROJECT_NAME} ${LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${BOOST}
			   ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)


target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
