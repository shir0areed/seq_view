cmake_minimum_required(VERSION 3.23)
project(SeqView)

add_subdirectory(seq_view)

option(SEQVIEW_BUILD_TEST "build test" OFF)
if(SEQVIEW_BUILD_TEST)
    add_subdirectory(test_project)
endif()
