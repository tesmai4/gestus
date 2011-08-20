// example 1 - load image, find faces, show, release

#include <cstdio>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "example.h"
using namespace std;


static CvHaarClassifierCascade * cascade=NULL;
static CvMemStorage            * storage=NULL;

static string testdata( const char* relative_file_name )
{
	char buf[1024]={0};
	GetModuleFileName(NULL, buf, sizeof(buf)-1);
	return string(buf) + "\\..\\..\\..\\testdata\\" + string(relative_file_name);
}

static void detectFaces( IplImage *img )
{
    int i;
 
    /* detect faces */
    CvSeq *faces = cvHaarDetectObjects(
            img,
            cascade,
            storage,
            1.1,
            3,
            0 /*CV_HAAR_DO_CANNY_PRUNNING*/,
            cvSize( 40, 40 ) );
 
    /* for each face found, draw a red box */
    for( i = 0 ; i < ( faces ? faces->total : 0 ) ; i++ ) {
        CvRect *r = ( CvRect* )cvGetSeqElem( faces, i );
        cvRectangle( img,
                     cvPoint( r->x, r->y ),
                     cvPoint( r->x + r->width, r->y + r->height ),
                     CV_RGB( 255, 0, 0 ), 1, 8, 0 );
    }
 
    /* display video */
    cvShowImage( "video", img );
}

int main2( int argc, char** argv )
{
  IplImage  *img;
  string kDefaultImageName = testdata( "myfingers.jpg" );
  string inputImageName;
  
  if (argc < 2) {
    printf("Using default image file name %s.\n", kDefaultImageName);
    inputImageName = kDefaultImageName;
  } else {
    inputImageName = argv[1];
  }

   string filename = testdata( "haarcascade_frontalface_alt.xml" );

  cascade = ( CvHaarClassifierCascade* )cvLoad( filename.c_str(), 0, 0, 0 );
  if (!cascade)
	  printf("\nCan't load cascade file '%s'", filename.c_str());

  storage = cvCreateMemStorage( 0 );
  if (!storage)
	  printf("\nCan't cvCreateMemStorage()");


  img     = cvLoadImage( inputImageName.c_str(), 1 ); 
  if (!img)
	  printf("\nCan't load image file '%s'", inputImageName.c_str());

  if ( cascade && storage && img )
  {
	  cvNamedWindow( "video", 1 );
	  detectFaces( img );
	  cvWaitKey( 0 );
	  cvDestroyWindow( "video" );
  }

  if (img)
		cvReleaseImage( &img );
  if (cascade)
		cvReleaseHaarClassifierCascade( &cascade );
  if (storage)
		cvReleaseMemStorage( &storage );

  return 0;
}
