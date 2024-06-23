cmake_minimum_required(VERSION 3.23)
project(SeqView)

add_subdirectory(seq_view)

option(SEQVIEW_BUILD_TEST "build test" OFF)
if(SEQVIEW_BUILD_TEST)
    add_subdirectory(test_project)
endif()

if(MSVC AND TARGET test_project)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT test_project)
endif()
