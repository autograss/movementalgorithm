#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "image.hpp"
#include "grass_analyzer.hpp"

using namespace std;

cv::Mat GrassAnalyzer::find_line(Image image)
{

    cv::Mat ycbr_image;
    cv::cvtColor(image.getCvImage(), ycbr_image, CV_RGB2GRAY);
    image.setYcbcrImage(ycbr_image);

    cv::Mat blurred_image;

    medianBlur(ycbr_image, blurred_image, 41);

    cv::Mat bin_image;
    threshold(blurred_image, bin_image, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::Mat threshold_image;
    threshold(bin_image, threshold_image, 0, 255, cv::THRESH_BINARY);

    float data[7][7] = {{1,1,1,1,1,1,1}, {1,1,1,1,1,1,1}};

    cv::Mat kernel = cv::Mat(2, 5, CV_32FC1, &data);


    cv::Mat dilate_image;
    dilate(threshold_image, dilate_image, kernel);

    return dilate_image;

}
