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
int main4( int argc, char** argv )
{
	CvCapture* capture = 0;
	capture = cvCaptureFromCAM(0);
	alpha = 0.1; 
	int track_bar_value = 10;
	Mat cur_frame; 
	Mat hist_frame, mask_gray, mask_binary;

	IplImage* image = NULL; // исходная картинка
	IplImage* image8 = NULL; // 8bit grey исходная картинка

	IplImage* lap = NULL;
	IplImage* lap8 = NULL;
	
	if(capture)
	{
		hist_frame = cvQueryFrame(capture);
		cvtColor(hist_frame, hist_frame, CV_BGR2GRAY);
		cvNamedWindow("edges");
		cvNamedWindow("moving edges");
		cvNamedWindow("binary");
		createTrackbar("alpha", "moving edges", &track_bar_value, 100, update_trackbar);
		while(cvWaitKey(10) <= 0)
		{
			image = cvQueryFrame(capture);
			Mat in = image;
			cvtColor(in, in, CV_BGR2GRAY);
			

			if (lap == NULL)
				lap = cvCreateImage( cvSize( image->width, image->height ), 
					IPL_DEPTH_16S, image->nChannels );

			if (lap8 == NULL)
				lap8 = cvCreateImage( cvGetSize(image), image->depth, image->nChannels);

			cvSmooth( image, image, CV_GAUSSIAN, 5, 5 );
			
			cvLaplace(image, lap, 5);
			//cvSobel(image, lap, 1, 1, 5);

			cvSmooth( lap, lap, CV_GAUSSIAN, 5, 5 );
			
			cvConvertScale(lap, lap8);// преобразуем изображение к 8-битному

			Mat matlap8 = lap8;
			cvtColor(matlap8, matlap8, CV_BGR2GRAY);
			adaptiveThreshold( matlap8, matlap8, 255, ADAPTIVE_THRESH_GAUSSIAN_C, 
				THRESH_BINARY, 5, -0.1 );

			cvShowImage("edges", lap8);

			cur_frame = lap8;

			cvtColor(cur_frame, cur_frame, CV_BGR2GRAY);
			addWeighted( cur_frame, alpha, hist_frame, 1 - alpha, 0.0, hist_frame);
			absdiff(hist_frame, cur_frame, mask_gray);
			imshow("moving edges", mask_gray);

			//adaptiveThreshold( mask_gray, mask_binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, 
			//	THRESH_BINARY, 25, -30 );

			threshold( mask_gray, mask_binary, 10, 255, cv::THRESH_BINARY );
			morphologyEx( mask_binary, mask_binary, cv::MORPH_CLOSE, cv::Mat() );
			morphologyEx( mask_binary, mask_binary, cv::MORPH_OPEN, Mat(5,5, CV_8UC1),
							  cv::Point( -1, -1 ), 1, cv::BORDER_CONSTANT, cv::Scalar( 0 ) );
			imshow("binary", mask_binary);
		}
		cvDestroyAllWindows();
		cvReleaseCapture(&capture);
	}

	return 0;
}