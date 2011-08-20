#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "example.h"
using namespace std;

// playing with cvThreshold() and cvFindContours()

int main4( int argc, char** argv )
{
    IplImage* src=0;
    // the first command line parameter must be file name of binary
    // (black-n-white) image

	string srcfile = argc < 2 ? testdata("myfingers_greyscale.jpg") : string(argv[1]);

	if( (src=cvLoadImage(srcfile.c_str(), 0))!= 0)
    {
        IplImage* dst = cvCreateImage( cvGetSize(src), 8, 3 );
        CvMemStorage* storage = cvCreateMemStorage(0);
        CvSeq* contour = 0;

        cvThreshold( src, src, 1, 128, CV_THRESH_OTSU ); ///CV_THRESH_BINARY );
		// http://opencv.willowgarage.com/documentation/miscellaneous_image_transformations.html?highlight=cvthreshold#cvThreshold

        cvNamedWindow( "Source", 1 );
        cvShowImage( "Source", src );

        cvFindContours( src, storage, &contour, sizeof(CvContour),
           CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
        cvZero( dst );

        for( ; contour != 0; contour = contour->h_next )
        {
            CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&255 );
            /* replace CV_FILLED with 1 to see the outlines */
            cvDrawContours( dst, contour, color, color, -1, CV_FILLED, 8 );
        }

        cvNamedWindow( "Components", 1 );
        cvShowImage( "Components", dst );
        cvWaitKey(0);

		cvDestroyWindow( "Components" );
		cvDestroyWindow( "Source" );
    }
	return 0;
}