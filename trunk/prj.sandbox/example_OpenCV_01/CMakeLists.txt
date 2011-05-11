PROJECT( example_OpenCV_01 )

SET( SOURCES src/example_OpenCV_01.cpp )

ADD_EXECUTABLE( example_OpenCV_01 ${SOURCES} )
TARGET_LINK_LIBRARIES( example_OpenCV_01 cv highgui )