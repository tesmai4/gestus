#include< cstdlib >
#include<iostream>
//#include< stdbool.h >
#include <cv.h>
#include "highgui.h"


#include "qd.h"

#define camera_in_use false

using namespace cv;

Mat my_opencv_read_image( void );


int main( int argc, char** argv)
{

if( camera_in_use )
{ 
	//write_file( true );
	return(0);
}
else
{
	//result = viola_jones( img );
	//write_file( &result );
	//Mat img;
	//img = my_opencv_read_image();
	//namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
    //imshow( "Display Image", img );
	//std::cout << img;
	//waitKey(0);
	//namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
	VideoCapture cap(0);
	if(!cap.isOpened())  // check if we succeeded
        printf("Shit happened\n");
	Mat frame;
	for( int i=0; i< 100; i++ )
	{
		cap >> frame;
		
		waitKey(40);
	}
	//imshow( "Display Image", frame );
	imwrite("testresult.jpg", frame);
	//waitKey(0);
}

return(0);
}

Mat my_opencv_read_image( void )
{
	VideoCapture cap(0);
	if(!cap.isOpened())  // check if we succeeded
        printf("Shit happened\n");
	Mat frame;	
	cap >> frame;
	
	//std::cout << img;
	
	return frame;
}
