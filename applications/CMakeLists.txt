project( ${ENIGMA} VERSION ${ENIGMA_VERSION} LANGUAGES CXX )
add_executable( ${ENIGMA} enigma_app.cxx )
target_link_libraries( ${ENIGMA} PUBLIC ${ENIGMA_LIBRARY} ${CPPLOGGER} )
