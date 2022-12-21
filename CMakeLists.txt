cmake_minimum_required(VERSION 3.24)
project(sq_UI)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_executable(sq_UI main.cpp include/widget.hpp include/vec2.hpp src/vec2.cpp include/margin.hpp src/margin.cpp src/widget.cpp include/key.hpp include/screen.hpp src/screen.cpp include/Widgets/box.hpp src/Widgets/box.cpp include/color.hpp src/color.cpp include/border.hpp include/gestureDetector.hpp src/gestureDetector.cpp include/rect.hpp src/rect.cpp include/Widgets/stack.hpp src/Widgets/stack.cpp include/invisibleWidget.hpp src/invisibleWidget.cpp include/overlay.hpp src/overlay.cpp include/Widgets/performanceOverlay.hpp include/Widgets/row.hpp src/Widgets/row.cpp include/Widgets/column.hpp src/Widgets/column.cpp include/Widgets/align.hpp src/Widgets/align.cpp src/Widgets/performanceOverlay.cpp include/Widgets/text.hpp src/Widgets/text.cpp include/Widgets/textInput.hpp src/Widgets/textInput.cpp include/Widgets/CustomButton.hpp src/Widgets/CustomButton.cpp include/Widgets/scrollable.hpp src/Widgets/scrollable.cpp include/Widgets/scrollBar.hpp src/Widgets/scrollBar.cpp include/Widgets/scrollableWithScrollbar.hpp src/Widgets/scrollableWithScrollbar.cpp include/Widgets/textBox.hpp src/Widgets/textBox.cpp)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(sq_UI PRIVATE glfw)
target_link_libraries(sq_UI PRIVATE "Dwmapi.lib" "D2d1.lib" "Dwrite.lib" "version.lib")