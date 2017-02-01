cmake_minimum_required(VERSION 2.8)
project(DisplayImage)
find_package(OpenCV REQUIRED)
add_executable(DisplayImage DisplayImage.cpp)
target_link_libraries(
	DisplayImage
	${OpenCV_LIBS}
)
#add_executable(Drawing_2 Drawing_2.cpp)
#target_link_libraries(
#	Drawing_2
#	${OpenCV_LIBS}
#)
#add_executable(Drawing_1 Drawing_1.cpp)
#target_link_libraries(
#	Drawing_1
#	${OpenCV_LIBS}
#)
add_executable(AddingImagesTrackbar AddingImagesTrackbar.cpp)
target_link_libraries(
	AddingImagesTrackbar
	${OpenCV_LIBS}
)
