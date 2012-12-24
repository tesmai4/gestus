// -- DRAFT -- 
// cam2avi (tool for saving test data as avi file) 
// based on tutorial article from http://www.cs.iit.edu/~agam/cs512/lect-notes/opencv-intro/opencv-intro.html
// see also discussion at http://www.compvision.ru/forum/index.php?showtopic=106



#include <opencv/cv.h>
#include <opencv/highgui.h>
#include < cstdlib >
#include <iostream>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "highlevelmonitorconfigurationapi.h"

#define COMPILE_MULTIMON_STUBS
#include "Winuser.h"
#include "multimon.h"
#include "windows.h"

//#include "example.h"
using namespace std;
#define NUMBER_OF_FRAME 50

HMONITOR MyMonitor(NULL);

int codec = //-1;
		/// CV_FOURCC('P','I','M','1'),
		/// -1, 
		CV_FOURCC('P','I','M','1');
		//CV_FOURCC('M', 'P', '4', '2');
		//CV_FOURCC('X', 'V', 'I', 'D');
int* detectAndDisplay( cv::Mat frame )
{
	vector<cv::Rect> faces;
	cv::Mat frame_gray;


	string face_cascade_name = "C:/gestus/trunk/data/lbpcascades/lbpcascade_frontalface.xml";
	string eyes_cascade_name = "C:/gestus/trunk/data/haarcascades/haarcascade_mcs_righteye.xml";
	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier eyes_cascade;
	string window_name = "Capture - Face detection";
	cv::RNG rng(126345);

	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return NULL; };
	if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return NULL; };

	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- Detect faces
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 7, 0|CV_HAAR_SCALE_IMAGE, cvSize(20, 20) );
	//for( int i(0); i < faces.size(); i++ )
	//{
		
		//cv::Mat faceROI = frame_gray( faces[i] );
		std::vector<cv::Rect> eyes;

		//--  detect eyes
		eyes_cascade.detectMultiScale( frame_gray, eyes, 1.1, 5, 0|CV_HAAR_SCALE_IMAGE, cvSize(25, 25) );

		for( size_t j = 0; j < eyes.size(); j++ )
		{
			cv::Point eye_center( eyes[j].x + eyes[j].width/2, eyes[j].y + eyes[j].height/2 );
			int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
			circle( frame, eye_center, radius, cvScalar( 255, 0, 0 ), 3, 8, 0 );
		}
	//}

	for (vector<cv::Rect>::iterator r = faces.begin(); r != faces.end(); r++)
		rectangle(frame, r->tl(), r->br(), cv::Scalar(0, 0, 255));

	imshow( window_name, frame );
	cv::waitKey( 5 );
	int arrey[2];
	arrey[0]= faces.size(); 
	arrey[1] = eyes.size();
	return(arrey);
}


BOOL WINAPI MonitorEnumProc( HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData  )
{
	MONITORINFOEX monInfo;
	DISPLAY_DEVICE monDevice;
	DEVMODE monMode;
	static DWORD num = 0;

	monInfo.cbSize = sizeof(monInfo);
	monDevice.cb = sizeof(monDevice);
	monMode.dmSize = sizeof(monMode);
	monMode.dmDriverExtra = 0;
	monMode.dmFields = DM_DISPLAYFREQUENCY;
	
	GetMonitorInfo( hMonitor, &monInfo );
	EnumDisplayDevices( monInfo.szDevice, num, &monDevice, 0 );
	if(monDevice.StateFlags != 0 && MyMonitor == NULL)
		MyMonitor = hMonitor;
	num++;
	return (TRUE);
}
bool changeBrightnessDisplay(bool reduce) // reduce == true - min brightness; reduce == false - max brightness
{
	 EnumDisplayMonitors( 0, 0, MonitorEnumProc, 0 );
	 DWORD cPhysicalMonitors;
	 LPPHYSICAL_MONITOR pPhysicalMonitors = NULL;
	 BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(MyMonitor, &cPhysicalMonitors);

	 if (bSuccess)
	 {
		 // Allocate the array of PHYSICAL_MONITOR structures.
		 pPhysicalMonitors = (LPPHYSICAL_MONITOR)malloc(
			 cPhysicalMonitors* sizeof(PHYSICAL_MONITOR));

		 if (pPhysicalMonitors != NULL)
		 {
			 // Get the array.
			 bSuccess = GetPhysicalMonitorsFromHMONITOR(MyMonitor, cPhysicalMonitors, pPhysicalMonitors);
			 LPDWORD pdwMonitorCapabilities(NULL);
			 LPDWORD pdwSupportedColorTemperatures(NULL);
			if (GetMonitorCapabilities ((*pPhysicalMonitors).hPhysicalMonitor, pdwMonitorCapabilities, pdwSupportedColorTemperatures))
			{
				LPDWORD pdwMinimumBrightness(NULL); 
				LPDWORD pdwCurrentBrightness(NULL); 
				LPDWORD pdwMaximumBrightness(NULL);
				if (!GetMonitorBrightness((*pPhysicalMonitors).hPhysicalMonitor, pdwMinimumBrightness, pdwCurrentBrightness, pdwMaximumBrightness))
					 printf("--(!)Error in find Monitor\n");

				else if (reduce && !SetMonitorBrightness((*pPhysicalMonitors).hPhysicalMonitor, *pdwMinimumBrightness ))
				{
					 printf("--(!)Error in set brightnes of Monitor\n");
					 bSuccess = FALSE;
				}
				else if (!reduce && !SetMonitorBrightness((*pPhysicalMonitors).hPhysicalMonitor, *pdwMaximumBrightness))
				{
					printf("--(!)Error in set brightnes of Monitor\n");
					bSuccess = FALSE;
				}
		
	 			// Close the monitor handles.
				bSuccess = DestroyPhysicalMonitors(cPhysicalMonitors, pPhysicalMonitors);
    			// Free the array.
				free(pPhysicalMonitors);
			}
		}
	 }
	 return bSuccess;
}

void searchGestures()
{
	cv::VideoCapture cap(0);//Capturing block begins
	if(!cap.isOpened())  // check if we succeeded
	{
		printf("Camera is not available\n");
		return;
	}
	cv::Mat frame;
	double result[(int)NUMBER_OF_FRAME];
	for( int i=0; i< (int)NUMBER_OF_FRAME; i++ )//This place is kinda dirty. The thing is - my webcam takes 3 sec to initialize. Until then, it returns it's own logo. Is it invariant for all cameras? Is it possible to "preinit the cam"? I do not know.
	{
		cap >> frame;
		//cvShowImage("detecting...", &static_cast<IplImage>(frame));
		//cv::waitKey(30);
		int* arrey = detectAndDisplay(frame);
		if (arrey != NULL)
		{
		    if (arrey[0] == 0 && arrey[1] > 0)
				result[i] = 0.5*arrey[1];
			else
				result[i] = arrey[0];
		}
		else
			result[i] = 0;
	}
	double totalResult(0);
	for(int i=0; i < (int)NUMBER_OF_FRAME; i++)
		totalResult += result[i];
	totalResult /= (double)NUMBER_OF_FRAME;

	if (totalResult <  0.4)
		changeBrightnessDisplay(true);
	
	FILE* resultfile = fopen( "../result.txt", "w");
	fprintf( resultfile, "%f users detected for %d frames\n",  totalResult, (int)NUMBER_OF_FRAME);
	fclose( resultfile );

	//waitKey(0);

}


int main(int argc, char** argv)
{
	searchGestures();	
	return 0;
}