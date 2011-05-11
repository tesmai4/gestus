#include <cstdio>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char **argv) {
  const char *kDefaultImageName = "MGC.jpg";
  const char *inputImageName = NULL;
  
  if (argc < 2) {
    printf("Using default image file name %s.\n", kDefaultImageName);
    inputImageName = kDefaultImageName;
  } else {
    inputImageName = argv[1];
  }

  // Load image.
  IplImage* img = cvLoadImage(inputImageName);

  // Prepare windows.
  cvNamedWindow("Example-in");
  cvNamedWindow("Example-out");

  // Show the original image.
  cvShowImage("Example-in", img);

  // Create an image for the output.
  IplImage *out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);

  // Perform a Gaussian blur.
  cvSmooth( img, out, CV_GAUSSIAN, 11, 11 );

  // Show the processed image.
  cvShowImage("Example-out", out);

  // Wait for key press and free used memory.
  cvWaitKey(0);
  cvReleaseImage(&img);
  cvReleaseImage(&out);
  cvDestroyWindow("Example3-in");
  cvDestroyWindow("Example3-out");
  
  return 0;
}
