cmake_minimum_required(VERSION 3.7)
project(symbol_table_demo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SymTable.cpp SymTable.h symTabRecord.cpp symTabRecord.h Utility.cpp Utility.h)
add_executable(symbol_table_demo ${SOURCE_FILES})