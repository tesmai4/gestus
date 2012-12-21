cmake_minimum_required(VERSION 2.8)

project( gestus-bin )
find_package( OpenCV REQUIRED )
add_executable( gestus-bin example.cpp )
add_executable( detector detector.cpp )
add_executable( detector_example objectDetection.cpp )
add_executable( detector_example2 objectDetection2.cpp )


target_link_libraries( gestus-bin ${OpenCV_LIBS} )
target_link_libraries( detector ${OpenCV_LIBS} )
target_link_libraries( detector_example ${OpenCV_LIBS} )
target_link_libraries( detector_example2 ${OpenCV_LIBS} )


