#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cvaux.h>

#include "example.h"

using namespace std;

int main3(int argc, char **argv)
{
	IplImage *frame = NULL;
	IplImage *mask = NULL;
	CvCapture *capture = cvCaptureFromCAM(0);
	cvNamedWindow("Camera");
	cvNamedWindow("Skin");
	while(1)
	{
		frame = cvQueryFrame(capture);
		if (!frame) 
			break;
		mask = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
		CvAdaptiveSkinDetector filter(1, CvAdaptiveSkinDetector::MORPHING_METHOD_ERODE);
		filter.process(frame, mask);
		cvShowImage("Camera", frame);
		cvShowImage("Skin", mask);
		char c = cvWaitKey(33);
		if (c == 27)
			break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Camera");
	return 0;
}