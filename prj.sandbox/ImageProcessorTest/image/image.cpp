#include "opencv.h"
#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include <string>
#include "stdlib.h"


using std::string;
//#define COLOR 50
#define UPEDGE 20
#define DOWNEDGE 20

IplImage* image = 0;
IplImage* src = 0;
IplImage* new_image, stub;


//Program works with one image now. It will be changed to several!!! 

int main(int argc, char* argv[])
{
		//load image
        //char* filename = argc == 2 ? argv[1] : "35_rec0404.bmp";
		
		for (int number = 0; number <= 33; number++)
		{
			string filename = "35_rec04";
			if (number<10) filename+="0";
			char buf[65];
			char* res;
			res = _itoa(number,buf,10);
			//string buf;
			//_itoa( number, buf, 10 );
			//_itoa_s(number,buf,2,10);
			//filename+=(char*)number;
			filename+=res;
			filename+=".bmp";
			image = cvLoadImage((char*)filename.c_str(),1);
			src = cvCloneImage(image);
			//

			//information of image and create window with image
			printf("[i] image: %s\n", filename);
			assert( src != 0 );
			cvNamedWindow("original",0);
			cvShowImage("original",image);
			printf( "[i] channels:  %d\n",        image->nChannels );
			printf( "[i] pixel depth: %d bits\n",   image->depth );
			printf( "[i] width:       %d pixels\n", image->width );
			printf( "[i] height:      %d pixels\n", image->height );
			printf( "[i] image size:  %d bytes\n",  image->imageSize );
			printf( "[i] width step:  %d bytes\n",  image->widthStep );
			//
			
			//create matrix of image
			//CvMat *mat = cvCreateMat(image->height,image->width,CV_32FC3 );
			//cvConvert( image, mat );
			CvMat stub1, *mat;
			mat = cvGetMat(image, &stub1, 0, 0);
			//

			//find of min and max values of matrix
			/*
			double min=0,max=0;
			printf("%d\n", (image->height)/2);
			printf("%d\n", (image->width)/2);
			for (int i=0; i<image->height; i++)
			{
				CvScalar scal = cvGet2D( mat,(image->width)/2,i);
				
				if (scal.val[0]>max)
				{
					max = scal.val[0];
				}
				if (min == 0)
				{
					min = scal.val[0];
				}
				else
				{
					if ((scal.val[0]<min) && (scal.val[0]!=0))
					{
						min = scal.val[0];
					}
				}
			}*/
			//

			//find center of image
			CvPoint* edge;
			CvPoint center;
			edge = new CvPoint[400];
			CvScalar scalUp,scalDown,scalLeft,scalRight;
			int i = (image->width/2- 50);
			//printf("%d\n",i);
			for (int k=0; k<100; k++)
			{
				int flag = 0;
				int j = 0;
				while(flag < 20)
				{
					scalUp = cvGet2D( mat,i,j);
					if ( (scalUp.val[0]>5) && (scalUp.val[0]<150) ) 
					{
						if ( !( (cvGet2D( mat,i+5,j).val[0]>5) && (cvGet2D( mat,i-5,j).val[0]>5) ) ) flag=0;
						flag++;
					}
					else flag=0;
					j++;
				}
				edge[k].x = i;
				edge[k].y = j-20;
				flag=0;
				j = image->height-1;
				while (flag < 20)
				{
					scalDown = cvGet2D(mat,i,j);
					if ( (scalDown.val[0]>5) && (scalDown.val[0]<150) )
					{
						if ( !( (cvGet2D( mat,i+5,j).val[0]>5) && (cvGet2D( mat,i-5,j).val[0]>5) ) ) flag=0;
						flag++;
					}
					else flag=0;
					j--;
				}
				edge[200+k].x =i;
				edge[200+k].y=j+20;
				i++;
				//printf("%d  %d  %f\t%d  %d  %f\n",edge[k].x, edge[k].y, scalUp.val[0], edge[200+k].x, edge[200+k].y, scalDown.val[0]);
			}
			double up=0,down=0;
			for (int k=0; k<100; k++)
			{
				up+=edge[k].y;
				down+=edge[200+k].y;
			}

			int j = (image->height/2- 50);
			for (int k=0; k<100; k++)
			{
				int flag = 0;
				int i = 0;
				while(flag < 20)
				{
					scalLeft = cvGet2D( mat,i,j);
					if ( (scalLeft.val[0]>5) && (scalLeft.val[0]<150) )
					{
						if ( !( (cvGet2D( mat,i,j+5).val[0]>5) && (cvGet2D( mat,i,j-5).val[0]>5) ) ) flag=0;
						flag++;
					}
					else flag=0;
					i++;
				}
				edge[300+k].x = i-20;
				edge[300+k].y = j;
				flag=0;
				i = image->width-10;
				
				while (flag < 20)
				{
					scalRight = cvGet2D(mat,i,j);
					if ( (scalRight.val[0]>5) && (scalRight.val[0]<150) )
					{
						if ( !( (cvGet2D( mat,i,j+5).val[0]>5) && (cvGet2D( mat,i,j-5).val[0]>5) ) ) flag=0;
						flag++;
					}
					else flag=0;
					i--;
				}
				edge[100+k].x = i+20;
				edge[100+k].y = j;
				j++;
				//printf("%d  %d  %f\t%d  %d  %f\n",edge[300+k].x, edge[300+k].y, scalLeft.val[0], edge[100+k].x, edge[100+k].y, scalRight.val[0]);
			}
			double left=0,right=0;
			for (int k=0; k<100; k++)
			{
				left+=edge[300+k].x;
				right+=edge[100+k].x;
			}
			left/=100;
			right/=100;
			up/=100;
			down/=100;
			center.y = (int)(up+down)/2;
			center.x = (int)(left+right)/2;
			//printf("x: %d  y: %d\n",center.x,center.y);
			//

			//find radius
			double r=0;
			for (int k=0; k<400; k++)
			{
				r += pow((center.x-edge[k].x)*(center.x-edge[k].x)+(center.y-edge[k].y)*(center.y-edge[k].y),0.5);
			}
			r/=400;
			//printf("%f\n",r);
			int rad = (int) r;
			//


			//true color
			int color=0;
			for (int i = 0; i <= rad; i++)
			{
				color+= (int) cvGet2D(mat,center.x+i,center.y).val[0];
			}
			color/=(rad+1);
			//printf("%d",color);
			/*int* colors;
			colors = new int[256];
			for (int i = 0; i < 256; i++)
			{
				colors[i]=0;
			}
			int buf=0;
			for (int i = 0; i <= rad; i++)
			{
				buf = (int) cvGet2D(mat,center.x+i,center.y).val[0];
				colors[buf]++;
			}
			for (int i = 0; i < 256; i++)
			{
				printf("%d ", i);
				for (int j = 0; j <= colors[i]; j++)
				{
					printf("*");
				}
				printf("\n");
			}*/
			//for (int i = 0; i <= rad; i++)
			//{
			//	printf("%d %d",center.x+i, (int) cvGet2D(mat,center.x+i,center.y).val[0]);
			//	/*for (int j = 0; j < (int) cvGet2D(mat,center.x+i,center.y).val[0]; j++)
			//	{
			//		printf("*");
			//	}*/
			//	printf("\n");
			//}
			//

			//main part
			for (int k = 1; k <= rad; k++)
			{
				double s = 0;
				int count = 0;
				int y = 0;
				int* elementsUp,* elementsDown;
				elementsUp = new int[2*k+1];
				elementsDown = new int[2*k+1];
				for (int x = -k; x <= k; x++)
				{
					y = (int) pow(k*k-x*x,0.5);
					elementsUp[x+k] = y;
					//if (k==100) printf("%d\t%d\n",x,y);
					elementsDown[x+k] = -y;
					//printf("%d\n",center.y+y);
					s+= cvGet2D(mat,center.x+x,center.y+y).val[0];
					count++;
					//if (y!=-y)
					if (1)
					{
						s+= cvGet2D(mat,center.x+x,center.y-y).val[0];
						count++;
					}
				}
				s/=count; //find average of matrix values on one pixel circle
				//printf("%f\n",s);
				CvScalar scalBuf;
				scalBuf.val[0]=color;
				scalBuf.val[1]=color;
				scalBuf.val[2]=color;
				for (int i=0; i<2*k+1; i++)
				{
					if ( (cvGet2D(mat,center.x+i-k,center.y+elementsUp[i]).val[0]>s-DOWNEDGE) && (cvGet2D(mat,center.x+i-k,center.y+elementsUp[i]).val[0]<s+UPEDGE) )
					{
						cvSet2D(mat,center.x+i-k,center.y+elementsUp[i],scalBuf);  //change value of matrix
					}
					if ( (cvGet2D(mat,center.x+i-k,center.y+elementsDown[i]).val[0]>s-DOWNEDGE) && (cvGet2D(mat,center.x+i-k,center.y+elementsDown[i]).val[0]<s+UPEDGE) )
					{
						cvSet2D(mat,center.x+i-k,center.y+elementsDown[i],scalBuf);  //change value of matrix
					}
				}
				/*cvSet2D(mat,center.x+i-k,center.y+elementsUp[i],scalBuf);
				cvSet2D(mat,center.x+i-k,center.y+elementsDown[i],scalBuf);*/
			}
			for (int k = 1; k <= rad; k++)
			{
				double s = 0;
				int count = 0;
				int x = 0;
				int* elementsUp,* elementsDown;
				elementsUp = new int[2*k+1];
				elementsDown = new int[2*k+1];
				for (int y = -k; y <= k; y++)
				{
					x = (int) pow(k*k-y*y,0.5);
					elementsUp[y+k] = x;
					//if (k==100) printf("%d\t%d\n",x,y);
					elementsDown[y+k] = -x;
					//printf("%d\n",center.y+y);
					s+= cvGet2D(mat,center.x+x,center.y+y).val[0];
					count++;
					//if (y!=-y)
					if (1)
					{
						s+= cvGet2D(mat,center.x-x,center.y+y).val[0];
						count++;
					}
				}
				s/=count; //find average of matrix values on one pixel circle
				//printf("%f\n",s);
				CvScalar scalBuf;
				scalBuf.val[0]=color;
				scalBuf.val[1]=color;
				scalBuf.val[2]=color;
				for (int i=0; i<2*k+1; i++)
				{
					if ( (cvGet2D(mat,center.x+elementsUp[i],center.y+i-k).val[0]>s-DOWNEDGE) && (cvGet2D(mat,center.x+elementsUp[i],center.y+i-k).val[0]<s+UPEDGE) )
					{
						cvSet2D(mat,center.x+elementsUp[i],center.y+i-k,scalBuf);  //change value of matrix
					}
					if ( (cvGet2D(mat,center.x+elementsDown[i],center.y+i-k).val[0]>s-DOWNEDGE) && (cvGet2D(mat,center.x+elementsDown[i],center.y+i-k).val[0]<s+UPEDGE) )
					{
						cvSet2D(mat,center.x+elementsDown[i],center.y+i-k,scalBuf);  //change value of matrix
					}
				}
			}
			

			//picture new image
			new_image = cvGetImage(mat, &stub);
			cvNamedWindow("new",0);
			cvShowImage("new",new_image);
			//
			filename.insert(0,"res_");
			cvSaveImage((char*)filename.c_str(),new_image,0);
			//exit program and release memory
			//cvWaitKey(0);
			cvReleaseImage(& image);
			
			cvReleaseImage(&src);
			
			cvDestroyWindow("original");
			cvDestroyWindow("new");
			//
		}
        return 0;
}