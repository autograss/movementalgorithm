#include <opencv2/opencv.hpp>
#include <iostream>
#include "image.hpp"


Image::Image(std::string imagePath)
{
  this->cvImage = cv::imread(imagePath);
  if (this->cvImage.empty())
  {
    std::cerr << "Class Image - ERROR: Not read image " << imagePath << std::endl;
    return;
  }
}

cv::Mat
Image::getBinaryImage(unsigned int pixelsToBinary, unsigned int pixelBinary)
{
  cv::Mat binary;
  cv::cvtColor(this->cvImage, binary, CV_BGR2GRAY);
  cv::threshold(binary, binary, pixelsToBinary, pixelBinary, cv::THRESH_BINARY);

  return binary;
}

cv::Mat
Image::getCvImage()
{
  return this->cvImage;
}

int
Image::getWidth()
{
  return this->cvImage.cols;
}

int
Image::getHeight()
{
  return this->cvImage.rows;
}
