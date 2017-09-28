cmake_minimum_required(VERSION 2.8.3)
project(qt5_gl_test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(SRC_FILES
  test.cpp
)

add_executable(qt5_gl_test ${SRC_FILES})
target_link_libraries(qt5_gl_test
    GL
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::OpenGL
)

