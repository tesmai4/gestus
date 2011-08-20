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
	//main1(argc,argv);
	//main2(argc,argv);
	//main3(argc,argv);
	//main4(argc,argv);
	//main5(argc,argv);

	return 0;
}
