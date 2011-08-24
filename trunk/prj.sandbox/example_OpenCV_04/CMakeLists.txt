PROJECT( example_OpenCV_04 )

SET( SOURCES
	src/example.h  
	src/example_OpenCV_04.cpp 
	src/example_OpenCV_04_1.cpp 
	src/example_OpenCV_04_2.cpp 
	src/example_OpenCV_04_3.cpp 
	src/example_OpenCV_04_4.cpp 
	src/example_OpenCV_04_5.cpp 
)

IF( MSVC )
# opencv 2.3.0
SET( LIBRARIES 

opencv_calib3d230d
opencv_contrib230d
opencv_core230d
opencv_features2d230d
opencv_flann230d
opencv_gpu230d
opencv_highgui230d
opencv_imgproc230d
opencv_legacy230d
opencv_ml230d
opencv_objdetect230d
opencv_video230d
###tbb_debug

)

ELSE()
  MESSAGE( FATAL_ERROR "Platform is not supported yet." )
ENDIF()

ADD_EXECUTABLE( example_OpenCV_04 ${SOURCES} )
TARGET_LINK_LIBRARIES( example_OpenCV_04 ${LIBRARIES} )