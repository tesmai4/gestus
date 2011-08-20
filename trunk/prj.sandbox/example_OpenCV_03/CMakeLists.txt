PROJECT( example_OpenCV_03 )

SET( SOURCES 
	src/example_OpenCV_03.cpp 
	src/example_OpenCV_03_1.cpp 
	src/example_OpenCV_03_2.cpp 
	src/example_OpenCV_03_3.cpp 
	src/example_OpenCV_03_4.cpp 
	src/example_OpenCV_03_5.cpp 
)

IF( MSVC )
  SET( LIBRARIES cv210 highgui210 cxcore210 )
ELSE()
  MESSAGE( FATAL_ERROR "Platform is not supported yet." )
ENDIF()

ADD_EXECUTABLE( example_OpenCV_03 ${SOURCES} )
TARGET_LINK_LIBRARIES( example_OpenCV_03 ${LIBRARIES} )