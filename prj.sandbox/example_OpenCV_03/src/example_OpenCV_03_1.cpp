#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "example.h"

using namespace std;

int main1(int argc, char **argv)
{
	string kDefaultImageName = testdata("myfingers.jpg");
	IplImage *img = cvLoadImage(kDefaultImageName.c_str());
	IplImage *out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvSmooth(img, out, CV_GAUSSIAN, 13, 13);
	cvNamedWindow("Source");
	cvNamedWindow("Destination");
	cvShowImage("Source", img);
	cvShowImage("Destination", out);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvReleaseImage(&out);
	cvDestroyWindow("Source");
	cvDestroyWindow("Destination");
	return 0;
}