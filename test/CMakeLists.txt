include_directories (.)
include_directories (../src)
include_directories (../examples/json)

set (TIPA_TEST_LIBRARY ${PROJECT_NAME}_test)

# Create Catch library to decrease compile times
add_library (${TIPA_TEST_LIBRARY} ${LIBRARY_TYPE} test_main.cpp)

# Define a macro to simplify tests creation
function (create_test name)
    add_executable (${name} ${ARGN})
    target_compile_features (${name} PRIVATE cxx_range_for)
    target_link_libraries (${name} ${TIPA_TEST_LIBRARY} ${PROJECT_NAME})
    add_test (NAME ${name} COMMAND ${name})
endfunction (create_test)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/struct.txt
    ${CMAKE_CURRENT_BINARY_DIR}/struct.txt COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lexer_multi.txt
    ${CMAKE_CURRENT_BINARY_DIR}/lexer_multi.txt COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lexer-test1.txt
    ${CMAKE_CURRENT_BINARY_DIR}/lexer-test1.txt COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parser-test1.txt
    ${CMAKE_CURRENT_BINARY_DIR}/parser-test1.txt COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parser-test2.txt
    ${CMAKE_CURRENT_BINARY_DIR}/parser-test2.txt COPYONLY)

create_test (TestCollector test_collector.cpp)
create_test (TestLexer     test_lexer.cpp)
create_test (TestLexer2    test_lexer2.cpp)
create_test (TestFile      test_file.cpp)
create_test (TestParser    test_parser.cpp)
create_test (TestWptr      test_wptr.cpp)
create_test (TestVisitor   test_visitor.cpp)
create_test (TestAction    test_action.cpp)
create_test (TestList      test_list.cpp)
create_test (TestErrorMsg  test_error_msg.cpp)

#Test Json
set (JSON_TEST_NAME test_json)
set (JSON_TEST_SOURCE test_json.cpp)
add_executable (${JSON_TEST_NAME} ${JSON_TEST_SOURCE})
target_compile_features (${JSON_TEST_NAME} PRIVATE cxx_range_for)
target_link_libraries (${JSON_TEST_NAME} ${TIPA_JSON_LIBRARY} ${TIPA_TEST_LIBRARY} ${PROJECT_NAME})
add_test (NAME ${JSON_TEST_NAME} COMMAND ${JSON_TEST_NAME})
