project(App)

add_executable(${PROJECT_NAME})
add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)

target_link_libraries(${PROJECT_NAME} 
                        PRIVATE FSM::Interface)


install(TARGETS ${PROJECT_NAME}
DESTINATION ${BINARY_DIR})
