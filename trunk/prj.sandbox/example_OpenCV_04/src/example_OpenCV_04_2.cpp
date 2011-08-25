#include "example.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
using namespace cv;
double alpha;
void update_trackbar(int val, void*)
{
	alpha = val / 100.0;
}
int main2( int argc, char** argv )
{
	CvCapture* capture = 0;
	capture = cvCaptureFromCAM(0);
	alpha = 0.1; 
	int track_bar_value = 10;
	Mat cur_frame, hist_frame, mask_gray, mask_binary;
	
	if(capture)
	{
		hist_frame = cvQueryFrame(capture);
		cvtColor(hist_frame, hist_frame, CV_BGR2GRAY);
		cvNamedWindow("gray");
		cvNamedWindow("binary");
		createTrackbar("alpha", "gray", &track_bar_value, 100, update_trackbar);
		while(cvWaitKey(10) <= 0)
		{
			cur_frame = cvQueryFrame(capture);
			cvtColor(cur_frame, cur_frame, CV_BGR2GRAY);
			addWeighted( cur_frame, alpha, hist_frame, 1 - alpha, 0.0, hist_frame);
			absdiff(hist_frame, cur_frame, mask_gray);
			imshow("gray", mask_gray);
			threshold( mask_gray, mask_binary, 10, 255, cv::THRESH_BINARY );
			morphologyEx( mask_binary, mask_binary, cv::MORPH_CLOSE, cv::Mat() );
			morphologyEx( mask_binary, mask_binary, cv::MORPH_OPEN, Mat(5,5, CV_8UC1),
							  cv::Point( -1, -1 ), 1, cv::BORDER_CONSTANT, cv::Scalar( 0 ) );
			imshow("binary", mask_binary);
		}
		cvDestroyWindow("gray");
		cvDestroyWindow("binary");
		cvReleaseCapture(&capture);
	}

	return 0;
}