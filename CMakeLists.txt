cmake_minimum_required (VERSION 3.11 FATAL_ERROR)

include (FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(
	ftxui 
	GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
	GIT_TAG 4d50dadb4167f356583cc2bb7b4257b340ba6275)
FetchContent_Declare(
	rapidfuzz
	GIT_REPOSITORY https://github.com/maxbachmann/rapidfuzz-cpp
	GIT_TAG d2c7de7002d7c9c274dc5a0205e393907033aa3f)
FetchContent_GetProperties(ftxui)
FetchContent_MakeAvailable(rapidfuzz)

if(NOT ftxui_POPULATED)
FetchContent_Populate(ftxui)
add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

project(tuibms LANGUAGES CXX VERSION 1.0.0)
add_executable(tuibms src/main.cpp src/AVLTree.cpp src/HashTable.cpp src/Book.cpp src/Loan.cpp src/Patron.cpp src/UI_Helper.cpp)
target_include_directories(tuibms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/tuibms PRIVATE src)
target_link_libraries(tuibms PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component PRIVATE rapidfuzz::rapidfuzz)
set_target_properties(tuibms PROPERTIES CXX_STANDARD 17)
