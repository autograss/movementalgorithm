#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp>
#include <string>

class Image
{
public:
  Image(std::string imagePath);

  cv::Mat getBinaryImage(unsigned int pixelsToBinary, unsigned int pixelBinary);
  cv::Mat getBinaryForegroundImage(unsigned int pixelsToBinary, unsigned int pixelBinary);
  cv::Mat getBinaryBackgroundImage(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor);
  cv::Mat getBinaryMarkersImage(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor);

  int getWidth();
  int getHeight();

  cv::Mat getCvImage();

private:
  cv::Mat cvImage;
};
#endif
