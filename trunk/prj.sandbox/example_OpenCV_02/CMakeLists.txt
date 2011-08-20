PROJECT( example_OpenCV_02 )

SET( SOURCES 
	src/example_OpenCV_02.cpp 
	src/example_OpenCV_02_1.cpp 
	src/example_OpenCV_02_2.cpp 
	src/example_OpenCV_02_3.cpp 
	src/example_OpenCV_02_4.cpp 
	src/example_OpenCV_02_5.cpp 
)

IF( MSVC )
  SET( LIBRARIES cv210 highgui210 cxcore210 )
ELSE()
  MESSAGE( FATAL_ERROR "Platform is not supported yet." )
ENDIF()

ADD_EXECUTABLE( example_OpenCV_02 ${SOURCES} )
TARGET_LINK_LIBRARIES( example_OpenCV_02 ${LIBRARIES} )