cmake_minimum_required(VERSION 3.24)
project(sq_UI)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_executable(sq_UI main.cpp include/widget.hpp include/vec2.hpp src/vec2.cpp include/margin.hpp src/margin.cpp src/widget.cpp include/key.hpp include/screen.hpp src/screen.cpp include/Widgets/box.hpp src/Widgets/box.cpp include/color.hpp src/color.cpp include/border.hpp include/gestureDetector.hpp src/gestureDetector.cpp include/rect.hpp src/rect.cpp include/Widgets/stack.hpp src/Widgets/stack.cpp include/invisibleWidget.hpp src/invisibleWidget.cpp)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(sq_UI PRIVATE glfw)
target_link_libraries(sq_UI PRIVATE "Dwmapi.lib" "D2d1.lib")