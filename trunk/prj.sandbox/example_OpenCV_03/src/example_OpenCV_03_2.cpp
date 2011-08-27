#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "example.h"

using namespace std;

int main2(int argc, char **argv)
{
	IplImage *frame = NULL;
	CvCapture *capture = cvCaptureFromCAM(0);
	cvNamedWindow("Camera");
	while(1)
	{
		frame = cvQueryFrame(capture);
		if (!frame) 
			break;
		cvSmooth(frame, frame, CV_GAUSSIAN, 15,15);
		cvShowImage("Camera", frame);
		char c = cvWaitKey(33);
		if (c == 27)
			break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Camera");
	return 0;
}