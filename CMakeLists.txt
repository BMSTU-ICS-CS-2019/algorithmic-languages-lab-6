cmake_minimum_required(VERSION 3.15)
project(lab_6)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        lab_6 main.cpp
        collections/collection.h collections/abstract_collection.h
        collections/queue.h collections/stack.h collections/linked_list.h
        util/cli_util.h
)