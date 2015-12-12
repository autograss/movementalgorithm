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

    medianBlur(ycbcr_channels[0], blurred_image, 41);

    cv::Mat bin_image;
    threshold(blurred_image, bin_image, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::Mat threshold_image;
    threshold(bin_image, threshold_image, 0, 255, cv::THRESH_BINARY);

    cv::Mat dilate_image;
    int kernel_size = 7;
    int kernel = [7][7];

    for (i = 0; i < kernel_size; i++) {
      for (j = 0; i < kernel_size; j++) {
      kernel[i][j] = 1;
    }

    dilate(threshold_image, dilate_image, kernel);

    return final_image;

}
