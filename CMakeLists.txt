cmake_minimum_required(VERSION 2.8.12)

project(QRcode)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(HEADERS "convex_hull.h" "makeWhite_outside_rect.h" "simplify_hull.h" "basic_geometry.h"
    "finding_corner_points.h" "gradient.h"  "sides_of_gradient_box.h" "boundary_point.h"
    "structures_point.h" "convert_in_monochrome.h" "make_img_from_gradient.h")
set(SOURCES "main.cpp" "convex_hull.cpp" "makeWhite_outside_rect.cpp" "simplify_hull.cpp" "basic_geometry.cpp"
    "finding_corner_points.cpp" "gradient.cpp" "sides_of_gradient_box.cpp" "boundary_point.cpp" "convert_in_monochrome.cpp" "make_img_from_gradient.cpp")

find_package(Qt5Core)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(QRcode ${HEADERS} ${SOURCES})


target_link_libraries(QRcode Qt5::Core)
target_link_libraries(QRcode  ${OpenCV_LIBS} )
