cmake_minimum_required(VERSION 3.2)

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR "Do not run cmake in-source. Instead run\n$ mkdir build\n$ cd build\n$ cmake ..\n")
endif ()

project(CssPreprocessor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Set Bison/Flex - generated content
find_package(BISON 3.0.2 REQUIRED)
find_package(FLEX 2.5.35 REQUIRED)

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
    src/lib/driver/Driver.cpp
    src/lib/logger/Logger.cpp
    src/lib/ast/node/Node.cpp src/lib/ast/node/Node.hpp src/lib/ast/modifier/Modifier.cpp src/lib/ast/modifier/Modifier.hpp src/lib/ast/property/Property.cpp src/lib/ast/property/Property.hpp src/lib/ast/value/string/String.cpp src/lib/ast/value/string/String.hpp src/lib/ast/value/value/Value.cpp src/lib/ast/value/value/Value.hpp src/lib/ast/value/color/Color.cpp src/lib/ast/value/color/Color.hpp src/lib/ast/value/number/Number.cpp src/lib/ast/value/number/Number.hpp src/lib/ast/value/variable/Variable.cpp src/lib/ast/value/variable/Variable.hpp src/lib/ast/value/calculation/Calculation.cpp src/lib/ast/value/calculation/Calculation.hpp src/lib/token/Token.cpp src/lib/token/Token.hpp)

add_executable(CssPreprocessor ${SOURCE_FILES} ${GENERATED_FILES})
target_link_libraries(CssPreprocessor fl)

# Add test target
set(TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
enable_testing()

FILE(GLOB TESTS_SIMPLE "${TEST_SOURCE_DIR}/simple/*.simple")
FOREACH (TEST ${TESTS_SIMPLE})
    get_filename_component(TESTNAME ${TEST} NAME)
    add_test(
        NAME ${TESTNAME}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND CssPreprocessor -f ${TEST}
        DEPENDS CssPreprocessor
    )
ENDFOREACH (TEST)
