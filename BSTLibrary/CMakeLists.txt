cmake_minimum_required(VERSION 3.26)
project(BST_23F)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BST_23F
        Book.cpp
        Book.hpp
        BST.cpp
        BST.hpp
        BSTMain.cpp
        BSTNode.cpp
        BSTNode.hpp
        Library.cpp
        Library.hpp)
