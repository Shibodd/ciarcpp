FetchContent_Declare (googletest GIT_REPOSITORY https://github.com/google/googletest.git
                                GIT_TAG v1.15.2
                                GIT_SHALLOW TRUE
)

set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

enable_testing()

add_executable (${PROJECT_NAME}_json_parse_tests ${CMAKE_CURRENT_LIST_DIR}/src/json_parse_tests.cpp)
target_link_libraries (${PROJECT_NAME}_json_parse_tests PRIVATE ${PROJECT_NAME}_json_parse GTest::gtest_main)

include (GoogleTest)
gtest_discover_tests (${PROJECT_NAME}_json_parse_tests)