cmake_minimum_required(VERSION 3.2)

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR "Do not run cmake in-source. Instead run\n$ mkdir build\n$ cd build\n$ cmake ..\n")
endif ()

project(cssp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-register")
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
include_directories(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR})
# / End of Bison/Flex

include_directories(src)
set(SOURCE_FILES
    src/main.cpp
    src/lib/driver/Driver.cpp
    src/lib/logger/Logger.cpp
    src/lib/ast/node/Node.cpp
    src/lib/ast/for/For.cpp
    src/lib/ast/modifier/Modifier.cpp
    src/lib/ast/property/Property.cpp
    src/lib/ast/value/string/String.cpp
    src/lib/ast/value/value/Value.cpp
    src/lib/ast/value/color/Color.cpp
    src/lib/ast/value/number/Number.cpp
    src/lib/ast/value/variable/Variable.cpp
    src/lib/ast/value/calculation/Calculation.cpp
    src/lib/token/Token.cpp
    src/lib/ast/separator/Separator.cpp
    src/lib/ast/selector/Selector.cpp
    src/lib/ast/block/Block.cpp
    src/lib/ast/import/Import.cpp
    src/lib/ast/variableSetter/VariableSetter.cpp
    src/lib/ast/media/Media.cpp
    src/lib/ast/mediaEntry/MediaEntry.cpp
    src/lib/ast/value/functionCall/FunctionCall.cpp
    src/lib/generator/Generator.cpp
    src/lib/main/Main.cpp
    )

add_executable(cssp ${SOURCE_FILES} ${GENERATED_FILES})
target_link_libraries(cssp fl)

# Add test target
enable_testing()
set(TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

FILE(GLOB TESTS_SIMPLE "${TEST_SOURCE_DIR}/simple/*.simple")
FOREACH (TEST ${TESTS_SIMPLE})
    get_filename_component(TESTNAME ${TEST} NAME)
    add_test(
        NAME ${TESTNAME}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND cssp -f ${TEST}
        DEPENDS cssp
    )
ENDFOREACH (TEST)

FILE(GLOB TESTS_IN_OUT "${TEST_SOURCE_DIR}/in_out/*.in")
FOREACH (TEST ${TESTS_IN_OUT})
    get_filename_component(TESTNAME ${TEST} NAME)
    add_test(
        NAME ${TESTNAME}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND ${TEST_SOURCE_DIR}/diff.sh ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${TEST}
        DEPENDS cssp
    )
ENDFOREACH (TEST)
