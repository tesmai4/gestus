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
	//main1(argc,argv); // starter, load+blur+show
	//main2(argc,argv); // detect face from still photo
	main3(argc,argv); // detect face from web-cam
	//main4(argc,argv); // cvTreshold(), cvFindContours()
	//main5(argc,argv); // template selection & tracking, mouse response

	return 0;
}
