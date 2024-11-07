cmake_minimum_required(VERSION 3.29)
project(HashFunction C)

set(CMAKE_C_STANDARD 11)

add_executable(HashFunction src/main.c
        src/HashTable.c
        include/HashTable.h)
