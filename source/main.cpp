#include <opencv2/opencv.hpp>
#include <string>
#include "image.hpp"


int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <image_path>" << std::endl;
    return -1;
  }

  std::string saveFilePath = "";
  if(argc > 2)
  {
    saveFilePath = argv[2];
  }

  Image image(argv[1]);
  unsigned int pixelBinary = 255;
  unsigned int pixelsToBinary = 150;
  unsigned int backgroundColor = 125;

  Image::show("Original", image.getCvImage());
  Image::show("Binary", image.getBinaryImage(pixelsToBinary, pixelBinary));
  Image::show("Foreground", image.getBinaryForegroundImage(pixelsToBinary, pixelBinary));
  Image::show("Background", image.getBinaryBackgroundImage(pixelsToBinary, pixelBinary, backgroundColor));
  Image::show("Markers", image.getBinaryMarkersImage(pixelsToBinary, pixelBinary, backgroundColor));
  Image::show("Watershed", image.getBinaryWatershedSegmenterImage(pixelsToBinary, pixelBinary, backgroundColor));

  Image::show("Black and White", image.convertInBlackAndWhiteByStrip(pixelsToBinary, pixelBinary, backgroundColor));

  if(!saveFilePath.empty())
  {
    cv::Mat blackWhite = image.convertInBlackAndWhiteByStrip(pixelsToBinary, pixelBinary, backgroundColor);
    cv::imwrite(saveFilePath, blackWhite);
  }

  cv::waitKey(0);

  return 0;
}
