cmake_minimum_required(VERSION 2.8.12)

project(QRcode)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(HEADERS "add.h" "makeWhite_outside_rect.h")
set(SOURCES "main.cpp" "add.cpp" "makeWhite_outside_rect.cpp")

find_package(Qt5Core)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(QRcode ${HEADERS} ${SOURCES})


target_link_libraries(QRcode Qt5::Core)
target_link_libraries(QRcode  ${OpenCV_LIBS} )
