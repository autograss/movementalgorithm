#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>


bool isWhitePixel(uchar *ptr, int j)
{
  return ptr[3*j+2] > 200 and ptr[3*j+1] > 200 and ptr[3*j+0] > 200;
}


int main(int argc, char** argv )
{
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0] << " <image_path>" << std::endl;
    return -1;
  }

  IplImage* img = cvLoadImage(argv[1]);

  for(int i = 0; i < img->height; i++)
  {
    uchar *ptr = (uchar*)(img->imageData + i * img->widthStep);
    for(int j = 0; j < img->width; j++)
    {
      if(!isWhitePixel(ptr, j))
      {
        //ptr[3*j+2] = 255; //Red
        //ptr[3*j+1] = 255; //Green
        //ptr[3*j+0] = 20; //Blue
      }
      ptr[3*j+2] = 255;
      ptr[3*j+1] = 255;
    }
  }

  cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
  cvShowImage("Example1", img);
  cvWaitKey(0);
  cvReleaseImage(&img);
  cvDestroyWindow("Example1");

  return 0;
}
