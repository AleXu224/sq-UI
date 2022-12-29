cmake_minimum_required(VERSION 3.22)
project(sq_UI)

set(LIBRARY_TARGET_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

file(GLOB_RECURSE all_files CONFIGURE_DEPENDS "src/*.cpp" "include/*.h")


# For debugging
# add_executable(sq_UI main.cpp ${all_files})

# For release
add_library(sq_UI ${all_files})
target_include_directories(sq_UI PUBLIC include)
target_include_directories(sq_UI PUBLIC include/Widgets)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(sq_UI PUBLIC glfw)
target_link_libraries(sq_UI PRIVATE "Dwmapi.lib" "D2d1.lib" "Dwrite.lib" "version.lib")