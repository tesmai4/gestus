PROJECT( example_OpenCV_01 )

SET( SOURCES 
	src/example_OpenCV_01.cpp 
	src/example_OpenCV_01_1.cpp 
	src/example_OpenCV_01_2.cpp 
	src/example_OpenCV_01_3.cpp 
	src/example_OpenCV_01_4.cpp 
	src/example_OpenCV_01_5.cpp 
)

IF( MSVC )
  SET( LIBRARIES cv210 highgui210 cxcore210 )
ELSE()
  MESSAGE( FATAL_ERROR "Platform is not supported yet." )
ENDIF()

ADD_EXECUTABLE( example_OpenCV_01 ${SOURCES} )
TARGET_LINK_LIBRARIES( example_OpenCV_01 ${LIBRARIES} )