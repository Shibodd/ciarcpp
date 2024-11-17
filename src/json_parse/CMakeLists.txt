# glaze
FetchContent_Declare (glaze GIT_REPOSITORY https://github.com/stephenberry/glaze.git
                           GIT_TAG main
                           GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable (glaze)

# date
FetchContent_Declare (time GIT_REPOSITORY https://github.com/HowardHinnant/date.git
                           GIT_TAG v3.0.3
                           GIT_SHALLOW TRUE)
FetchContent_MakeAvailable (time)

add_library (${PROJECT_NAME}_json_parse ${CMAKE_CURRENT_LIST_DIR}/src/parse.cpp ${CMAKE_CURRENT_LIST_DIR}/src/serialize.cpp)
set_property (TARGET ${PROJECT_NAME}_json_parse PROPERTY POSITION_INDEPENDENT_CODE True)
target_link_libraries (${PROJECT_NAME}_json_parse PRIVATE glaze::glaze)
target_include_directories (${PROJECT_NAME}_json_parse PRIVATE ${time_SOURCE_DIR}/include/) # date.hpp
target_include_directories (${PROJECT_NAME}_json_parse PUBLIC ${CMAKE_SOURCE_DIR}/include/) # types.hpp
target_include_directories (${PROJECT_NAME}_json_parse PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/) # parse.hpp