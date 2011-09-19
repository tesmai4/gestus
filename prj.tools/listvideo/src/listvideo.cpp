// -- DRAFT -- 
// listvideo 

#include <opencv/cv.h>
#include <opencv/highgui.h>

//#include "example.h"
using namespace std;

void listvideo( const char* videofile = NULL )
{
	if (videofile == NULL)
		//videofile = "H:\\243CANON\\MVI_2230.MOV"; 
		//videofile = "c:\\temp\\video\\mvi_2230.avi";
		videofile = "c:\\temp\\out.avi";

	CvCapture* capture = cvCreateFileCapture( videofile );

	// get capture device properties:
	cvQueryFrame(capture); // this call is necessary to get correct 
                       // capture properties
	int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	int numFrames = (int) cvGetCaptureProperty(capture,  CV_CAP_PROP_FRAME_COUNT);
	// the total frame count is relevant for video files only. It does not seem to be working properly.

	if (capture)
	{
		IplImage* img = 0; 
		int nFrames = 50;
		
		cvNamedWindow("testing...", CV_WINDOW_AUTOSIZE);

		for(int key=' '; key ==' '; key=cvWaitKey())
		{
			cvGrabFrame(capture);          // capture a frame
			img=cvRetrieveFrame(capture);  // retrieve the captured frame
			cvShowImage("testing...", img); 
		}
		
		cvDestroyWindow("testing...");
	}
	else // !(capture) 
	{
		if (!capture)
			printf("\nCouldn't access video file ");
	}

	if (capture) //releasing the capture
		cvReleaseCapture(&capture);
}

int main(int argc, char** argv)
{
	listvideo( argc > 1 ? argv[1] : NULL );	
	return 0;
}