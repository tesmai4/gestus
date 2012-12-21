#include< cstdlib >
#include<iostream>
//#include< stdbool.h >
#include <cv.h>
//#include "highgui.h"
 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"


#include "qd.h"

#define camera_in_use false

using namespace cv;


int detectAndDisplay( Mat frame );

int main( int argc, char** argv)
{

if( camera_in_use )
{ 
	//write_file( true );
	return(0);
}
else
{
	
	VideoCapture cap(0);//Capturing block begins
	if(!cap.isOpened())  // check if we succeeded
        printf("Shit happened\n");
	Mat frame;
	for( int i=0; i< 100; i++ )//This place is kinda dirty. The thing is - my webcam takes 3 sec to initialize. Until then, it returns it's own logo. Is it invariant for all cameras? Is it possible to "preinit the cam"? I do not know.
	{
		cap >> frame;
		
		waitKey(40);
	}
	detectAndDisplay( frame );
	//int c = waitKey(0);
	//Capturing block ends. frame  is our capture frame
	
	//imshow( "Display Image", frame );
	imwrite("testresult.jpg", frame);
	
	
	//waitKey(0);
}

return(0);
}

int detectAndDisplay( Mat frame )
{
  std::vector<Rect> faces;
  Mat frame_gray;

  
  String face_cascade_name = "data/haarcascade_frontalface_alt_tree.xml";
  CascadeClassifier face_cascade;
  string window_name = "Capture - Face detection";
  RNG rng(12345);
  
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  
  
  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
  
  printf(" Detected faces: %d\n", faces.size());

  for( int i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

  }
  //-- Show what you got
  imshow( window_name, frame );
  waitKey( 0 );
  
  return(1);
 }
