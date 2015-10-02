#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp>
#include <string>

class Image
{
public:
  Image(std::string imagePath);

  cv::Mat getBinaryImage(unsigned int pixelsToBinary, unsigned int pixelBinary);

  int getWidth();
  int getHeight();
  cv::Mat getCvImage();

private:
  cv::Mat cvImage;
};
#endif
