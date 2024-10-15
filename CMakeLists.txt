cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
# requires Ninja or Makefile generator
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
# set this to run cmake without using a vs developer command prompt
set(CMAKE_MAKE_PROGRAM "C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/Ninja")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(imgui_exploration C CXX)

file(GLOB MAIN_SRC "src/*.cpp"  "vendor/imgui/backends/imgui_impl_dx11.cpp" "vendor/imgui/backends/imgui_impl_win32.cpp")
file(GLOB IMGUI_SRC "vendor/imgui/*.cpp")
add_executable(${PROJECT_NAME} ${MAIN_SRC})
add_library(imgui SHARED STATIC ${IMGUI_SRC})
add_library(testplug MODULE "src/testplug.cpp")

find_package(DirectX11 REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC "include" "vendor/imgui" ${DirectX11_INCLUDE_DIRS})
target_include_directories(testplug PUBLIC "include" "vendor/imgui")
target_include_directories(imgui PUBLIC "vendor/imgui")

target_link_libraries(testplug PRIVATE imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui ${DirectX11_LIBRARIES})
