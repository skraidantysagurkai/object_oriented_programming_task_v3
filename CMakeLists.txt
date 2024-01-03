cmake_minimum_required(VERSION 3.26)
project(OP_v2)

set(CMAKE_CXX_STANDARD 11)

add_executable(OP main.cpp
        libraries.h
        Student.cpp
        Student.h
        TextReader.cpp
        TextReader.h
        UserInterface.cpp
        UserInterface.h
        FileGenerator.cpp
        FileGenerator.h
        Person.cpp
        Person.h
)

# Add optimization flags
target_compile_options(OP PRIVATE -O3)
