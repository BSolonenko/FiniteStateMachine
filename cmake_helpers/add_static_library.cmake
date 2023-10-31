function(MakeStaticLibraryStructure)
    set(oneValueArgs INTERFACE_NAME)
    set(multiValueArgs PUBLIC_LIBS PRIVATE_LIBS)
    cmake_parse_arguments(ARG "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT ARG_INTERFACE_NAME)
        set(ARG_INTERFACE_NAME ${PROJECT_NAME})
    endif()

    add_library(${PROJECT_NAME} STATIC)
    add_library(${ARG_INTERFACE_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

    message(STATUS "${ARG_INTERFACE_NAME}::${PROJECT_NAME} created")

    file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
    target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

    target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

    target_link_libraries(${PROJECT_NAME}
        PUBLIC ${ARG_PUBLIC_LIBS}
        PRIVATE ${ARG_PRIVATE_LIBS}
    )
endfunction()
