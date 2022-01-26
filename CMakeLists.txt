cmake_minimum_required(VERSION 3.21)
project(sort)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

file(GLOB SRC src/*.cc src/*.h)

add_executable(sort ${SRC})
target_link_libraries(sort PRIVATE fmt)
target_compile_options(sort PRIVATE
        -Wall -Wextra -Wundef -Werror=return-type -Wconversion -Wpedantic
        -Wno-gnu-zero-variadic-macro-arguments -Wno-dollar-in-identifier-extension)
if (${CMAKE_CXX_COMPILER} STREQUAL "clang++")
    target_compile_options(sort PRIVATE -Xclang -fcolor-diagnostics)
endif ()
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_options(sort PRIVATE -O3)
else ()
    target_compile_options(sort PRIVATE -O0 -ggdb)
endif ()
