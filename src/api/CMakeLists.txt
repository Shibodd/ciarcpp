SET (CPR_ENABLE_SSL OFF)
FetchContent_Declare (cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 1.11.0
                         GIT_SHALLOW TRUE
                         EXCLUDE_FROM_ALL)
FetchContent_GetProperties(cpr)
if(NOT cpr_POPULATED)
  FetchContent_Populate(cpr)
  add_subdirectory(${cpr_SOURCE_DIR} ${cpr_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_library (${PROJECT_NAME} SHARED ${CMAKE_CURRENT_LIST_DIR}/api.cpp)
target_link_libraries (${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_json_parse)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../json_parse/include)
target_include_directories (${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

set_property (TARGET cpr PROPERTY POSITION_INDEPENDENT_CODE True)

install (TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install (DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/../)

install (EXPORT ${PROJECT_NAME}Config
         FILE ${PROJECT_NAME}Config.cmake
         NAMESPACE ${PROJECT_NAME}::
         DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)