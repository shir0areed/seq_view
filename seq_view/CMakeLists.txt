cmake_minimum_required(VERSION 3.23)

project(seq_view)

add_library(${PROJECT_NAME} INTERFACE)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET headers TYPE HEADERS BASE_DIRS include FILES
        include/seq_view.hpp
)

install(TARGETS ${PROJECT_NAME} FILE_SET headers)
