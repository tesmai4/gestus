#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "example.h"
using namespace std;

string testdata( const char* relative_file_name )
{
	char buf[1024]={0};
	GetModuleFileName(NULL, buf, sizeof(buf)-1);// win32 - ok...
	return string(buf) + "\\..\\..\\..\\testdata\\" + string(relative_file_name);
}

int main(int argc, char **argv) 
{
	//main1(argc,argv); // canny & hough example
	//main2(argc,argv); // convexHull()
	//main3(argc,argv); // "Advanced" skin detection example
	//main4(argc,argv); // moving edges
	main5(argc,argv);

	return 0;
}
