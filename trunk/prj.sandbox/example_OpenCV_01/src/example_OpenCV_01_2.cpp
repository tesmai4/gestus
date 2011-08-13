// example 1 - load image, find faces, show, release

#include <cstdio>

#include <opencv/cv.h>
#include <opencv/highgui.h>

static CvHaarClassifierCascade * cascade=NULL;
static CvMemStorage            * storage=NULL;

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
  const char *kDefaultImageName = "\\projects\\gestus\\testdata\\myfingers.jpg";
  const char *inputImageName = NULL;
  
  if (argc < 2) {
    printf("Using default image file name %s.\n", kDefaultImageName);
    inputImageName = kDefaultImageName;
  } else {
    inputImageName = argv[1];
  }

  char      *filename = 
		"\\projects\\gestus\\testdata\\"
		"haarcascade_frontalface_alt.xml";

  cascade = ( CvHaarClassifierCascade* )cvLoad( filename, 0, 0, 0 );
  storage = cvCreateMemStorage( 0 );

  img     = cvLoadImage( inputImageName, 1 ); 

  assert( cascade && storage && img );

  cvNamedWindow( "video", 1 );
  detectFaces( img );
  cvWaitKey( 0 );
  cvDestroyWindow( "video" );
  cvReleaseImage( &img );
  cvReleaseHaarClassifierCascade( &cascade );
  cvReleaseMemStorage( &storage );

  return 0;
}
