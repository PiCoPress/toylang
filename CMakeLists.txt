cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

project(toylang
    VERSION 0.0.1
    DESCRIPTION "Toylang is a programming Language for learning purposes."
    LANGUAGES CXX C
)

include(FetchContent)
FetchContent_Declare(
        googletest 
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        )
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)
