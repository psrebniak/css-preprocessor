cmake_minimum_required(VERSION 3.2)

if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR "Do not run cmake in-source. Instead run\n$ mkdir build\n$ cd build\n$ cmake ..\n")
endif()

project(CssPreprocessor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Set Bison/Flex - generated content
find_package(BISON 3.0.4 REQUIRED)
find_package(FLEX 2.6.0 REQUIRED)

set(GENERATED_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_OUTPUT_DIRECTORY})

BISON_TARGET(Parser src/parser.y ${GENERATED_OUTPUT_DIRECTORY}/parser.cpp)
FLEX_TARGET(Scanner src/lexer.l ${GENERATED_OUTPUT_DIRECTORY}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

set(GENERATED_FILES ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS})
include_directories(${CMAKE_BINARY_DIR})
# / End of Bison/Flex


include_directories(src)
set(SOURCE_FILES
        src/main.cpp
        src/lib/driver/Driver.cpp)

add_executable(CssPreprocessor ${SOURCE_FILES} ${GENERATED_FILES})
target_link_libraries(CssPreprocessor fl)
