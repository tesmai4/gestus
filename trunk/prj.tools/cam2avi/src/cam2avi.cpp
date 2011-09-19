// -- DRAFT -- 
// cam2avi (tool for saving test data as avi file) 
// based on tutorial article from http://www.cs.iit.edu/~agam/cs512/lect-notes/opencv-intro/opencv-intro.html
// see also discussion at http://www.compvision.ru/forum/index.php?showtopic=106

#include <opencv/cv.h>
#include <opencv/highgui.h>

//#include "example.h"
using namespace std;

int codec = 
		/// CV_FOURCC('P','I','M','1'),
		/// -1, 
		///CV_FOURCC('D', 'I', 'V', 'X'),
		CV_FOURCC('X', 'V', 'I', 'D');

void test()
{
	CvCapture* capture = cvCreateFileCapture( "c:\\temp\\out.avi" );

	// get capture device properties:
	cvQueryFrame(capture); // this call is necessary to get correct 
                       // capture properties
	int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	int numFrames = (int) cvGetCaptureProperty(capture,  CV_CAP_PROP_FRAME_COUNT);
	// the total frame count is relevant for video files only. It does not seem to be working properly.

	// initializing a video writer:
	CvVideoWriter *writer = 0;
	int isColor = 1;

	if (!fps)
		fps = 25;  // or 30  ?????????
	///int frameW  = 640; // 744 for firewire cameras ??????????
	///int frameH  = 480; // 480 for firewire cameras ??????????

	writer=cvCreateVideoWriter(
		"c:\\temp\\out2.avi",  // TODO: pass as argument, or, maybe automate name and placement
		// TODO: experiment with different codecs, select high quality and compact:
		codec,
		fps,							// TODO: why 25 fps, 640x480, color==true ?? ask camera!
		cvSize(frameW,frameH),			// ...
		isColor);						// ...

	//////Other possible codec codes:
	//////CV_FOURCC('P','I','M','1')    = MPEG-1 codec
	//////CV_FOURCC('M','J','P','G')    = motion-jpeg codec (does not work well)
	//////CV_FOURCC('M', 'P', '4', '2') = MPEG-4.2 codec
	//////CV_FOURCC('D', 'I', 'V', '3') = MPEG-4.3 codec
	//////CV_FOURCC('D', 'I', 'V', 'X') = MPEG-4 codec
	//////CV_FOURCC('U', '2', '6', '3') = H263 codec
	//////CV_FOURCC('I', '2', '6', '3') = H263I codec
	//////CV_FOURCC('F', 'L', 'V', '1') = FLV1 codec
	//////A codec code of -1 will open a codec selection window (in windows).


	if (capture && writer)
	{

		// Writing the video file:
		IplImage* img = 0; 
		int nFrames = 100;
		
		cvNamedWindow("testing...", CV_WINDOW_AUTOSIZE);

		for(int i=0;i<nFrames;i++)
		{
			cvGrabFrame(capture);          // capture a frame
			img=cvRetrieveFrame(capture);  // retrieve the captured frame
			cvWriteFrame(writer,img);      // add the frame to the file

			//To view the captured frames during capture, add the following in the loop:
			cvShowImage("testing...", img); 
			int key=cvWaitKey(20);           // wait 20 ms
			//Note that without the 20[msec] delay the captured sequence is not displayed properly.
		}
		
		cvDestroyWindow("testing...");
	}
	else // !(capture && writer) 
	{
		if (!capture)
			printf("\nCouldn't access video file ");
		if (!writer)
			printf("\nCouldn't create video file2 writer");
	}

	if (capture) //releasing the capture
		cvReleaseCapture(&capture);

	if (writer)  //releasing the video writer
		cvReleaseVideoWriter(&writer);
}

int main(int argc, char** argv)
{
    // initialize camera
	CvCapture* capture = cvCaptureFromCAM( 0 );

	// get capture device properties:
	cvQueryFrame(capture); // this call is necessary to get correct 
                       // capture properties
	int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	int numFrames = (int) cvGetCaptureProperty(capture,  CV_CAP_PROP_FRAME_COUNT);
	// the total frame count is relevant for video files only. It does not seem to be working properly.

	// initializing a video writer:
	CvVideoWriter *writer = 0;
	int isColor = 1;

	if (!fps)
		fps = 25;  // or 30  ?????????
	///int frameW  = 640; // 744 for firewire cameras ??????????
	///int frameH  = 480; // 480 for firewire cameras ??????????

	writer=cvCreateVideoWriter(
		"c:\\temp\\out.avi",  // TODO: pass as argument, or, maybe automate name and placement
		// TODO: experiment with different codecs, select high quality and compact:
		codec,
		fps,							// TODO: why 25 fps, 640x480, color==true ?? ask camera!
		cvSize(frameW,frameH),			// ...
		isColor);						// ...

	//////Other possible codec codes:
	//////CV_FOURCC('P','I','M','1')    = MPEG-1 codec
	//////CV_FOURCC('M','J','P','G')    = motion-jpeg codec (does not work well)
	//////CV_FOURCC('M', 'P', '4', '2') = MPEG-4.2 codec
	//////CV_FOURCC('D', 'I', 'V', '3') = MPEG-4.3 codec
	//////CV_FOURCC('D', 'I', 'V', 'X') = MPEG-4 codec
	//////CV_FOURCC('U', '2', '6', '3') = H263 codec
	//////CV_FOURCC('I', '2', '6', '3') = H263I codec
	//////CV_FOURCC('F', 'L', 'V', '1') = FLV1 codec
	//////A codec code of -1 will open a codec selection window (in windows).


	if (capture && writer)
	{

		// Writing the video file:
		IplImage* img = 0; 
		int nFrames = 100;
		
		cvNamedWindow("capturing...", CV_WINDOW_AUTOSIZE);

		for(int i=0;i<nFrames;i++)
		{
			cvGrabFrame(capture);          // capture a frame
			img=cvRetrieveFrame(capture);  // retrieve the captured frame
			cvWriteFrame(writer,img);      // add the frame to the file

			//To view the captured frames during capture, add the following in the loop:
			cvShowImage("capturing...", img); 
			int key=cvWaitKey(20);           // wait 20 ms
			//Note that without the 20[msec] delay the captured sequence is not displayed properly.
		}
		
		cvDestroyWindow("capturing...");
	}
	else // !(capture && writer) 
	{
		if (!capture)
			printf("\nCouldn't access camera");
		if (!writer)
			printf("\nCouldn't create video file writer");
	}

	if (capture) //releasing the capture
		cvReleaseCapture(&capture);

	if (writer)  //releasing the video writer
		cvReleaseVideoWriter(&writer);


	test();
	
	return 0;
}