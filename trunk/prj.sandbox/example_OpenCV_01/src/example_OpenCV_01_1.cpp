// example 1 - load image, show, blur, show, wait key, release

#include <cstdio>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>
using namespace std;

static string testdata( const char* relative_file_name )
{
	char buf[1024]={0};
	GetModuleFileName(NULL, buf, sizeof(buf)-1);
	return string(buf) + "\\..\\..\\..\\testdata\\" + string(relative_file_name);
}

int main1(int argc, char **argv) 
{
  string kDefaultImageName = testdata("myfingers.jpg");
  string inputImageName;
  
  if (argc < 2) {
	  printf("Using default image file name %s.\n", kDefaultImageName.c_str());
    inputImageName = kDefaultImageName;
  } else {
    inputImageName = argv[1];
  }

  // Load image.
  IplImage* img = cvLoadImage(inputImageName.c_str());
  if (img == NULL)
  {
	  printf("\nCan't load image '%s'", inputImageName.c_str() ); 
	  return -1;
  }

  // Prepare windows.
  cvNamedWindow("input image");
  cvNamedWindow("smoothed image");

  // Show the original image.
  cvShowImage("input image", img);

  // Create an image for the output.
  IplImage *out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);

  // Perform a Gaussian blur.
  cvSmooth( img, out, CV_GAUSSIAN, 11, 11 );

  // Show the processed image.
  cvShowImage("smoothed image", out);

  // Wait for key press and free used memory.
  cvWaitKey(0);
  cvReleaseImage(&img);
  cvReleaseImage(&out);
  cvDestroyWindow("input image");
  cvDestroyWindow("smoothed image");
  
  return 0;
}
