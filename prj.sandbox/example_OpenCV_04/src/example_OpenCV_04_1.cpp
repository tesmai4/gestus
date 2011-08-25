//using example from http://robot-develop.org/archives/2328

#include "example.h"
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <sys/timeb.h>
#include <vector>
using namespace std;


struct VMotionDetector
{
public:
    VMotionDetector( const cv::Size& imageSize, double cycleTime ) :
        m_previousImage( cv::Mat::zeros( imageSize, CV_8UC1 ) ),
        m_motionHistoryImage( imageSize, CV_32FC1 ),
        m_openingKernel( 5, 5, CV_8UC1 ),
        m_segmask( imageSize, CV_32FC1 ),
        m_maxMotionGradient( 1.5 * cycleTime ),
        m_motionHistoryDuration( 7 * cycleTime )
		{
		}

    void detectMovingRegions( const cv::Mat& currentFrame, double timestamp,
		std::vector<cv::Rect>& targets , cv::Mat& mask ) {
			cv::GaussianBlur( currentFrame, m_bluredImage, cv::Size( 3, 3 ), -1 );
			cv::absdiff( m_bluredImage, m_previousImage, mask );
			cv::threshold( mask, mask,  MOTION_THRESHOLD, 255, cv::THRESH_BINARY );
			cv::morphologyEx( mask, mask, cv::MORPH_CLOSE, cv::Mat() );
			cv::morphologyEx( mask, mask, cv::MORPH_OPEN, m_openingKernel,
							  cv::Point( -1, -1 ), 1, cv::BORDER_CONSTANT, cv::Scalar( 0 ) );
			cv::updateMotionHistory( mask, m_motionHistoryImage, timestamp, m_motionHistoryDuration );
			mask = m_motionHistoryImage;
			//cv::segmentMotion( m_motionHistoryImage, m_segmask, targets, timestamp, m_maxMotionGradient );

		//	std::vector<cv::Rect>::iterator endIt = targets.end( );
			//for( std::vector<cv::Rect>::iterator it = targets.begin( ); it != targets.end();) {
			//	if( cv::countNonZero( mask( * it ) ) < MIN_CONTOUR_AREA )
			//	{
			//		if(it != targets.begin())
			//		{
			//			std::vector<cv::Rect>::iterator prev = it;
			//			--prev;
			//			targets.erase( it );
			//			it = prev;
			//			++it;
			//		}
			//		else
			//		{
			//			targets.erase(it);
			//			it = targets.begin();
			//		}
			//	}
			//	else
			//	{
			//		++it;
			//	}
			//}

			m_bluredImage.copyTo( m_previousImage );
		}

    double getMotionHistoryDuration( ) const {
        return m_motionHistoryDuration;
    }

private:
    VMotionDetector& operator=( const VMotionDetector& );
    VMotionDetector( const VMotionDetector& );

    cv::Mat m_previousImage;
    cv::Mat m_motionHistoryImage;
    cv::Mat m_bluredImage;

    cv::Mat m_openingKernel;

    cv::Mat m_segmask;

    double m_maxMotionGradient;

    double m_motionHistoryDuration;

    static const double MOTION_THRESHOLD;
    static const double MIN_CONTOUR_AREA;
};
const double VMotionDetector::MOTION_THRESHOLD = 10;
const double VMotionDetector::MIN_CONTOUR_AREA = 150;
const double CYCLE_TIME = 0.02;


int main1(int argc, char** argv)
{
	CvCapture* capture = 0;
	capture = cvCaptureFromCAM(0);
	cv::Mat tmp_frame, gray_frame, out_frame;
	tmp_frame = cvQueryFrame(capture);

	VMotionDetector motionDetector(tmp_frame.size(), CYCLE_TIME);

    std::vector<cv::Rect> targets;
    std::vector<cv::Rect>::iterator it, endIt;

    cv::namedWindow("motion");
    cv::namedWindow("video");

    timeb startTime; 
	ftime(&startTime);
    timeb previousTime, cur_time = startTime;
	double tmp_time = 0;
	if(capture)
	{
		while( cv::waitKey(10) < 0 )
		{
			previousTime = cur_time;

			tmp_frame = cvQueryFrame(capture);
			cv::cvtColor(tmp_frame, gray_frame, CV_BGR2GRAY);

			ftime(&cur_time);
			tmp_time = cur_time.time * 100 + cur_time.millitm - startTime.time * 100 - startTime.millitm;
			motionDetector.detectMovingRegions(gray_frame, tmp_time, targets, out_frame);
			endIt = targets.end();
			/*for( it = targets.begin(); it != endIt; ++it )
				cv::rectangle(out_frame, *it, cv::Scalar( 255, 255, 0 ) );*/

			cv::imshow("motion", out_frame);
			cv::imshow("video", tmp_frame);

			ftime(&cur_time);
			tmp_time = cur_time.time * 100 + cur_time.millitm - previousTime.time * 100 - previousTime.millitm;
		}
		cvDestroyWindow("motion");
		cvDestroyWindow("video");
		cvReleaseCapture(&capture);
	}

	return 0;
}