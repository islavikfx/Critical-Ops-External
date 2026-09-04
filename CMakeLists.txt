cmake_minimum_required(VERSION 3.28.3)
project(ShiticalOps VERSION 1.2.3 LANGUAGES C CXX ASM)
set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)


add_executable(ShiticalOps
src/main.cpp
src/menu/Menu.cpp
src/memory/Memory.cpp
src/input/TouchInput.cpp
${IMGUI_DIR}/imgui.cpp
${IMGUI_DIR}/imgui_draw.cpp
${IMGUI_DIR}/imgui_tables.cpp
${IMGUI_DIR}/imgui_widgets.cpp
${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
${IMGUI_DIR}/backends/imgui_impl_android.cpp)

target_include_directories(ShiticalOps PRIVATE 
src 
${IMGUI_DIR} 
${IMGUI_DIR}/backends)

target_compile_definitions(ShiticalOps PRIVATE 
IMGUI_IMPL_OPENGL_ES2
NDEBUG
ANDROID)

find_library(EGL-lib EGL)
find_library(GLESv3-lib GLESv3)
find_library(android-lib android)
find_library(log-lib log)

target_link_libraries(ShiticalOps 
${EGL-lib} 
${GLESv3-lib} 
${android-lib}
${log-lib}
c++_static 
dl)

target_compile_options(ShiticalOps PRIVATE 
-Wall -O3 -fPIE 
-fno-rtti -ffunction-sections 
-fdata-sections -fvisibility=hidden -flto)

target_link_options(ShiticalOps PRIVATE 
-pie -Wl,--gc-sections -Wl,--no-undefined
-Wl,-z,relro,-z,now -Wl,--as-needed -flto)
