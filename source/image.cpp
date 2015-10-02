#include <opencv2/opencv.hpp>
#include <iostream>
#include "image.hpp"

const unsigned int Image::DEFAULT_PIXELS_BINARY = 255;
const unsigned int Image::DEFAULT_PIXELS_TO_BINARY = 100;

Image::Image(std::string imagePath)
{
  this->cvImage = cv::imread(imagePath);
  if (this->cvImage.empty())
  {
    std::cerr << "Class Image - ERROR: Not read image " << imagePath << std::endl;
    return;
  }
  setImageBinary(Image::DEFAULT_PIXELS_TO_BINARY, Image::DEFAULT_PIXELS_BINARY);
}

void
Image::setImageBinary(unsigned int pixelsToBinary, unsigned int pixelBinary)
{
  cv::cvtColor(this->cvImage, this->cvImageBinary, CV_BGR2GRAY);
  cv::threshold(this->cvImageBinary, this->cvImageBinary, pixelsToBinary, pixelBinary, cv::THRESH_BINARY);
}

cv::Mat
Image::getCvImage()
{
  return this->cvImage;
}

cv::Mat
Image::getCvImageBinary()
{
  return this->cvImageBinary;
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
