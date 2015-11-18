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
  if(this->cvImage.channels() == 3)
  {
    cv::cvtColor(this->cvImage, binary, CV_BGR2GRAY);
  } else {
    binary = this->cvImage.clone();
  }
  cv::threshold(binary, binary, pixelsToBinary, pixelBinary, cv::THRESH_BINARY);

  return binary;
}

cv::Mat
Image::getBinaryForegroundImage(unsigned int pixelsToBinary, unsigned int pixelBinary)
{
  cv::Mat foreground;
  cv::Mat binary = getBinaryImage(pixelsToBinary, pixelBinary);
  cv::erode(binary, foreground, cv::Mat(), cv::Point( -1, -1), 2);

  return foreground;
}

cv::Mat
Image::getBinaryBackgroundImage(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor)
{
  cv::Mat background;
  cv::Mat binary = getBinaryImage(pixelsToBinary, pixelBinary);
  cv::dilate(binary, background, cv::Mat(), cv::Point(-1,-1), 3);
  cv::threshold(background, background, 1, backgroundColor, cv::THRESH_BINARY_INV);

  return background;
}

cv::Mat
Image::getBinaryMarkersImage(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor)
{
  cv::Mat binary = getBinaryImage(pixelsToBinary, pixelBinary);
  cv::Mat foreground = getBinaryForegroundImage(pixelsToBinary, pixelBinary);
  cv::Mat background = getBinaryBackgroundImage(pixelsToBinary, pixelBinary, backgroundColor);

  cv::Mat markers(binary.size(), CV_8U, cv::Scalar(0));
  markers = foreground + background;

  return markers;
}

cv::Mat
Image::getBinaryWatershedSegmenterImage(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor)
{
  cv::Mat markers = getBinaryMarkersImage(pixelsToBinary, pixelBinary, backgroundColor);

  WatershedSegmenter segmenter;
  segmenter.setMarkers(markers);

  cv::Mat result = segmenter.process(this->cvImage);
  result.convertTo(result, CV_8U);

  return result;
}

cv::Mat
Image::convertInBlackAndWhiteByStrip(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor)
{
  int erodeWhite = 10;
  cv::Mat watershed = getBinaryWatershedSegmenterImage(pixelsToBinary, pixelBinary, backgroundColor);

  cv::threshold(watershed, watershed, 254, 255, cv::THRESH_BINARY);

  watershed = removeBlackAndWhiteNoise(watershed, erodeWhite);

  return watershed;
}

cv::Mat
Image::removeBlackAndWhiteNoise(cv::Mat binary, int erodeWhite)
{
  cv::Mat foreground;
  cv::erode(binary, foreground, cv::Mat(), cv::Point( -1, -1), erodeWhite);

  cv::Mat background;
  cv::dilate(binary, background, cv::Mat(), cv::Point(-1,-1), 2);
  cv::threshold(background, background, 1, 100, cv::THRESH_BINARY_INV);

  cv::Mat markers(binary.size(), CV_8U, cv::Scalar(0));
  markers = foreground + background;

  WatershedSegmenter segmenter;
  segmenter.setMarkers(markers);

  cv::Mat result = segmenter.process(this->cvImage);
  result.convertTo(result, CV_8U);

  cv::threshold(result, result, 254, 255, cv::THRESH_BINARY);

  return result;
}

std::vector< std::vector<int> >
Image::getPixelMatrix()
{
  return Image::getPixelMatrix(this->cvImage);
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

cv::Mat
Image::getCvImage()
{
  return this->cvImage;
}

void
Image::show(std::string label, cv::Mat image){
  cv::imshow(label, image);
}

std::vector< std::vector<int> >
Image::getPixelMatrix(cv::Mat image)
{
  std::vector< std::vector<int> > pixelMatrix;

  for(int row = 0; row < image.rows; row++)
  {
    std::vector<int> vectorColumn;
    for(int col = 0; col < image.row(row).cols; col++)
    {
      int pixelColor = image.at<uchar>(row, col);
      vectorColumn.push_back(pixelColor);
    }
    pixelMatrix.push_back(vectorColumn);
  }

  return pixelMatrix;

}
