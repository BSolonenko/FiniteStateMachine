project(FSM)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::Interface ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
