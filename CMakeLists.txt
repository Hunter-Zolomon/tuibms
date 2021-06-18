cmake_minimum_required (VERSION 3.11 FATAL_ERROR)

include (FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI)
FetchContent_GetProperties(ftxui)

if(NOT ftxui_POPULATED)
FetchContent_Populate(ftxui)
add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

project(tuibms LANGUAGES CXX VERSION 0.2.0)
add_executable(tuibms src/main.cpp src/AVLTree.cpp src/HashTable.cpp)
target_include_directories(tuibms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/tuibms PRIVATE src)
target_link_libraries(tuibms PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component)
set_target_properties(tuibms PROPERTIES CXX_STANDARD 17)