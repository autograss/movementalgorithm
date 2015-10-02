#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp>
#include <string>

class Image
{
public:
  static const unsigned int DEFAULT_PIXELS_BINARY;
  static const unsigned int DEFAULT_PIXELS_TO_BINARY;

  Image(std::string imagePath);

  void setImageBinary(unsigned int pixelsToBinary, unsigned int pixelBinary);

  int getWidth();
  int getHeight();
  cv::Mat getCvImage();
  cv::Mat getCvImageBinary();

private:
  cv::Mat cvImage;
  cv::Mat cvImageBinary;
};
#endif
