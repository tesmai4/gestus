// example got from http://nashruddin.com/OpenCV_Face_Detection


/**
 * Display video from webcam and detect faces
 */
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
 
static CvHaarClassifierCascade *cascade;
static CvMemStorage            *storage;
 
 
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
 
int main3( int argc, char** argv )
{
    CvCapture *capture=0;
    IplImage  *frame=0;
    int       key=0;
    char      *filename = 
		"..\\..\\gestus\\testdata\\"
		"haarcascade_frontalface_alt.xml";
 
    /* load the classifier
       note that I put the file in the same directory with
       this code */
    cascade = ( CvHaarClassifierCascade* )cvLoad( filename, 0, 0, 0 );
 
    /* setup memory buffer; needed by the face detector */
    storage = cvCreateMemStorage( 0 );
 
    /* initialize camera */
    capture = cvCaptureFromCAM( 0 );
 
    /* always check */
    assert( cascade && storage && capture );
 
    /* create a window */
    cvNamedWindow( "video", 1 );
 
    while( key <= 0 ) // key != 'q'
	{
        /* get a frame */
        frame = cvQueryFrame( capture );
 
        /* always check */
        if( !frame ) break;
 
        /* 'fix' frame */
        //////cvFlip( frame, frame, -1 );
        //////frame->origin = 0;
 
        /* detect faces and display video */
        detectFaces( frame );
 
        /* quit if user press 'q' */
        key = cvWaitKey( 10 );
    }
 
    /* free memory */
    cvReleaseCapture( &capture );
    cvDestroyWindow( "video" );
    cvReleaseHaarClassifierCascade( &cascade );
    cvReleaseMemStorage( &storage );
 
    return 0;
}
