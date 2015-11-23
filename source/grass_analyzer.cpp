#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "image.hpp"
#include "grass_analyzer.hpp"

using namespace std;

Image GrassAnalyzer::find_line(Image image)
{

    cv::Mat ycbr_image;
    cv::cvtColor(image.getCvImage(), ycbr_image, CV_RGB2YCrCb);
    image.setYcbcrImage(ycbr_image);
    return image;

}
