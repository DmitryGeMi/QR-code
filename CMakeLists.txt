cmake_minimum_required(VERSION 2.8.12)

project(QRcode)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(HEADERS "convex_hull.h" "makeWhite_outside_rect.h" "simplifying_hall.h" "basicfun.h"
    "finding_corner_points.h" "gradient.h"  "framing_window.h" "boundary_point.h" "structures.h")
set(SOURCES "main.cpp" "convex_hull.cpp" "makeWhite_outside_rect.cpp" "simplifying_hall.cpp" "basicfun.cpp"
    "finding_corner_points.cpp" "gradient.cpp" "framing_window.cpp" "boundary_point.cpp")

find_package(Qt5Core)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(QRcode ${HEADERS} ${SOURCES})


target_link_libraries(QRcode Qt5::Core)
target_link_libraries(QRcode  ${OpenCV_LIBS} )
