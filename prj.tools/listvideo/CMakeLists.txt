PROJECT( listvideo )

SET( SOURCES 
	src/listvideo.cpp 
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

ADD_EXECUTABLE( listvideo ${SOURCES} )
TARGET_LINK_LIBRARIES( listvideo ${LIBRARIES} )