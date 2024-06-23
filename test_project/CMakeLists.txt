cmake_minimum_required(VERSION 3.23)

project(test_project)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(${PROJECT_NAME} PRIVATE seq_view)

target_sources(${PROJECT_NAME} PRIVATE
        test_project.cpp
)
