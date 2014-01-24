/*this program is for displaying the obstacles in red-yellow-grey. I used a function called background which  takes an image as argument and returns a pointer to a one by three array that when multiplied by 10, gives the average pixel value of background.the time is not taken into account here */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

//void readme();
int * background (Mat image)
{   int x;
    static int r[3]={0};
    
    for (int k=0;k<3;k++)
    { double p[26]={0};
        { for (int m=0;m<image.cols;m=m+900)
            for(int n=0;n<image.rows;n=n+900)
            {
                x= image.data[image.step[0]*n + image.step[1]* m + k] ;    //getting the pixel values
                
                if (x<10)
                    p[0]=p[0]+1;
                else if (10<=x && x<20)
                    p[1]=p[1]+1;
                else if (20<=x && x<30)
                    p[2]=p[2]+1;
                else if (30<=x && x<40)
                    p[3]=p[3]+1;
                else if (40<=x && x<50)
                    p[4]=p[4]+1;
                else if (50<=x && x<60)
                    p[5]=p[5]+1;
                else if (60<=x && x<70)
                    p[6]=p[6]+1;
                else if (70<=x && x<80)
                    p[7]=p[7]+1;
                else if (80<=x && x<90)
                    p[8]=p[8]+1;
                else if (90<=x && x<100)
                    p[9]=p[9]+1;
                else if (100<=x && x<110)
                    p[10]=p[10]+1;
                else if (110<=x && x<120)
                    p[11]=p[11]+1;
                else if (120<=x && x<130)
                    p[12]=p[12]+1;
                else if (130<=x && x<140)
                    p[13]=p[13]+1;
                else if (140<=x && x<150)
                    p[14]=p[14]+1;
                else if (150<=x && x<160)
                    p[15]=p[15]+1;
                else if (160<=x && x<170)
                    p[16]=p[16]+1;
                else if (170<=x && x<180)
                    p[17]=p[17]+1;
                else if (180<=x && x<190)
                    p[18]=p[18]+1;
                else if (190<=x && x<200)
                    p[19]=p[19]+1;
                else if (200<=x && x<210)
                    p[20]=p[20]+1;
                else if (210<=x && x<220)
                    p[21]=p[21]+1;
                else if (220<=x && x<230)
                    p[22]=p[22]+1;
                else if (230<=x && x<240)
                    p[23]=p[23]+1;
                else if (240<=x && x<250)
                    p[24]=p[24]+1;
                
                else p[25]=p[25]+1;
            }
        }
        //cout<< p[25];
        int temp = 0;
        for(int l=1;l<26;l++)
        {
            if(p[l]>p[l-1])
                temp=l;
        }
        r[k]=temp;
    }
    return r;
}



int main()
{ int j=3;
    
    Mat drawing_array[3];      //contour drawing begins
  //  Mat drawing_array1[3];
    Mat threshold_image;
    
    for (int i=0;i<j;i++)
    {
        string p = to_string(i+1);
        Mat image;
        image = imread("/Users/msr8976/Downloads/bll"+p+".jpg",CV_LOAD_IMAGE_COLOR); //read file
        
        
        Mat imagefilt;
        
        medianBlur(image,imagefilt,9);
        
       GaussianBlur( imagefilt, imagefilt,Size(7,7),0,0,BORDER_DEFAULT );  //applying gaussian filter
            Mat image2;
        cvtColor(imagefilt,image2,CV_BGR2HSV);
        
//        int x= image2.data[image2.step[0]*20 + image2.step[1]* 20 + 0] ;   //getting the pixel values
//        int y= image2.data[image2.step[0]*20 + image2.step[1]* 20 + 1] ;
//        int z= image2.data[image2.step[0]*20 + image2.step[1]* 20 + 2] ;
//        
//        
//        inRange(image2, Scalar(x-50,y-60,z-60),Scalar(x+35,y+30,z+50),threshold_image);
     
        int * g;
        g= background(image2);
        int ro[3]={0};
        for (int t=0;t<3;t++)
        {
            ro[t]=*(g+t);
        }
        
       //cout<< ro[0];
       Mat threshold_image;
        
inRange(image2, Scalar(ro[0]*10-45,ro[1]*10-55,ro[2]*10-55),Scalar(ro[0]*10+40,ro[1]*10+35,ro[2]*10+55),threshold_image);
       
        bitwise_not(threshold_image,threshold_image );

        int dilation_size=4;
        Mat element2 = getStructuringElement( MORPH_RECT,
                                             Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                             Point( dilation_size, dilation_size ) );
        
        dilate(threshold_image,threshold_image,element2);
        
        
        int erode_sz =8;
        Mat element = getStructuringElement(MORPH_ELLIPSE,Size(2*erode_sz+1, 2*erode_sz+1),Point(erode_sz,erode_sz) );
        erode(threshold_image, threshold_image, element);
        
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(threshold_image,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
        vector<vector<Point> > contours_poly( contours.size() );
        
        for( int p = 0; p < contours.size(); p++ )
        {        approxPolyDP( Mat(contours[p]), contours_poly[p],3, true );
        }
        
        Mat drawing = Mat::zeros( threshold_image.size(), CV_8UC3 );
  
        for( int q = 0; q< contours.size(); q++ )
        {
            if (i<j-1)
            { Scalar color = Scalar(10+i*30,170+i*30,182+i*30);
            
            drawContours( drawing, contours_poly, q, color, CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
            }
            else
            {   Scalar color = Scalar(0,0,255);
                drawContours( drawing, contours_poly, q, color,CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
            }
        }
        
        drawing_array[i]=drawing;
        
    }

    //adding the arrays
    Mat sum= Mat::zeros( drawing_array[1].size(), CV_8UC3 );
   // Mat sum1= Mat::zeros( threshold_image.size(), CV_8UC3 );

    for (int a=0;a<j;a++)
    {  if (a<j-1)
        sum=sum+drawing_array[a];
       else
       {for (int k=0;k < sum.rows;k++)
        for (int m=0;m<sum.cols;m++)
            {if (drawing_array[a].data[drawing_array[a].step[0]*k + drawing_array[a].step[1]* m + 2]>0)
               {sum.data[sum.step[0]*k + sum.step[1]* m + 0]=sum.data[sum.step[0]*k + sum.step[1]* m + 1]=0;
                sum.data[sum.step[0]*k + sum.step[1]* m + 2]=255;   //red replacement
               }
             if(sum.data[sum.step[0]*k + sum.step[1]* m + 0]==0 && sum.data[sum.step[0]*k + sum.step[1]* m + 1]==0 && sum.data[sum.step[0]*k + sum.step[1]* m + 2]==0)
              { sum.data[sum.step[0]*k + sum.step[1]* m + 0]=sum.data[sum.step[0]*k + sum.step[1]* m + 1]=sum.data[sum.step[0]*k + sum.step[1]* m + 2]=85;    //grey fillup
              }
            }
       }
        //      sum1=sum1+drawing_array1[i];
    }

    namedWindow("detected",WINDOW_AUTOSIZE);
    imshow("detected",sum);                 //contour drawing ends
    imwrite("/Users/msr8976/Downloads/sum.jpg",sum);

    waitKey(0);
    return 0;
}


/* this blending code is not required now
 /// Read image ( same size, same type )      //blending begins
 Mat src1 = imread("/Users/msr8976/Downloads/bll1.jpg",CV_LOAD_IMAGE_COLOR);
 Mat src2 = imread("/Users/msr8976/Downloads/bll2.jpg",CV_LOAD_IMAGE_COLOR);
 
 if( !src1.data ) { printf("Error loading src1 \n"); return -1; }
 if( !src2.data ) { printf("Error loading src2 \n"); return -1; }
 
 Mat dst;
 
 for (int i=1;i<j;i++)
 {
 
 //     string s1= to_string(i+1);
 
 double alpha = 0.7; double beta; //double input;
 
 
 //    /// Ask the user enter alpha
 //    std::cout<<" Simple Linear Blender "<<std::endl;
 //    std::cout<<"-----------------------"<<std::endl;
 //    std::cout<<"* Enter alpha [0-1]: ";
 //    std::cin>>input;
 //
 //    /// We use the alpha provided by the user if it is between 0 and 1
 //    if( input >= 0.0 && input <= 1.0 )
 //    { alpha = input; }
 
 
 /// Create Windows
 namedWindow("Linear Blend", 1);
 
 beta = ( 1.0 - alpha );
 addWeighted( src1, alpha, src2, beta, 0.0, dst);
 
 src1=dst;
 string s = to_string(i+2);
 cout<<s;
 
 if (i<j-1)
 src2 = imread("/Users/msr8976/Downloads/bll"+s+".jpg",CV_LOAD_IMAGE_COLOR);
 
 //        imshow("src1",src1);
 //        imshow("src2",src2);
 
 
 }       //end of for loop
 
 imshow("dst",dst);
 Mat total=sum1+dst;
 imshow("total",total);
 imwrite("/Users/msr8976/Downloads/sum.jpg",sum);    //blending ends
 imwrite("/Users/msr8976/Downloads/total.jpg",total);    //blending ends  */
