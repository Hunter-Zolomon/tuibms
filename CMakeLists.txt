cmake_minimum_required (VERSION 3.11)

include (FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI)
FetchContent_GetProperties(ftxui)

if(NOT ftxui_POPULATED)
FetchContent_Populate(ftxui)
add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

project(ftxui-project LANGUAGES CXX VERSION 0.0.1)
add_executable(ftxui-project src/main.cpp)
target_include_directories(ftxui-project PRIVATE src)
target_link_libraries(ftxui-project PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component)
set_target_properties(ftxui-project PROPERTIES CXX_STANDARD 17)