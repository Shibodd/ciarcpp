SET (CPR_ENABLE_SSL OFF)
FetchContent_Declare (cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 1.11.0
                         GIT_SHALLOW TRUE)
FetchContent_MakeAvailable (cpr)

add_library (${PROJECT_NAME} SHARED ${CMAKE_CURRENT_LIST_DIR}/api.cpp)
target_link_libraries (${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_json_parse)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../json_parse/include)