#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "image.hpp"
#include "grass_analyzer.hpp"

using namespace std;

cv::Mat GrassAnalyzer::find_line(Image image)
{

    cv::Mat ycbr_image;
    cv::cvtColor(image.getCvImage(), ycbr_image, CV_RGB2YCrCb);
    image.setYcbcrImage(ycbr_image);
    cv::Mat ycbcr_channels[3];
    split(ycbr_image, ycbcr_channels);

    cv::Mat blurred_image;

    medianBlur(ycbcr_channels[0], blurred_image, 51);

    cv::Mat bin_image;
    threshold(blurred_image, bin_image, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    return bin_image;

}
