cmake_minimum_required(VERSION 2.8.12)

project(QRcode)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(HEADERS "convex_hull.h" "makeWhite_outside_rect.h" "simplify_hull.h" "basic_geometry.h"
    "finding_corner_points.h" "gradient.h"  "mark_candidate_for_barcode.h" "boundary_point.h"
    "structures_point.h" "convert_in_monochrome.h" "make_img_from_gradient.h" "hog_basic_instrument.h"
    "two_peaks_of_hog.h" "structures_four_directions.h" "ccl_algorithm.h" "sides_framework_white_pixels.h"
    "compressive_img_candidate_for_barcode.h" "create_img_marker.h" "input_parameters_output_barcode_ang.h")

set(SOURCES "main.cpp" "convex_hull.cpp" "makeWhite_outside_rect.cpp" "simplify_hull.cpp" "basic_geometry.cpp"
    "finding_corner_points.cpp" "gradient.cpp" "mark_candidate_for_barcode.cpp" "boundary_point.cpp"
    "convert_in_monochrome.cpp"  "make_img_from_gradient.cpp" "hog_basic_instrument.cpp"
    "two_peaks_of_hog.cpp" "ccl_algorithm.cpp" "sides_framework_white_pixels.cpp"
    "compressive_img_candidate_for_barcode.cpp" "create_img_marker.cpp" "input_parameters_output_barcode_ang.cpp")


find_package(Qt5Core)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${gtest_INCLUDE_DIRS} )

add_executable(QRcode ${HEADERS} ${SOURCES})


target_link_libraries(QRcode Qt5::Core)
target_link_libraries(QRcode  ${OpenCV_LIBS} )
target_link_libraries(QRcode  ${gtest_LIBS} )
