#include< stdlib.h >
#include< stdbool.h >
#include "qd.h"


int main( int argc, char** argv)
{

if( camera_in_use() )
{ 
	write_file( true );
	return(0);
}
else
{
	img = opencv_read_image();
	result = viola_jones( img );
	write_file( &result );
}

return(0);
}
