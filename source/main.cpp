#include <opencv2/opencv.hpp>
#include <string>
#include "image.hpp"
#include "black_white_analyzer.hpp"
#include "grass_analyzer.hpp"

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
  unsigned int pixelsToBinary = 100;
  unsigned int backgroundColor = 125;

  BlackWhiteAnalyzer analyzer;
  std::vector< std::vector<int> > matrixPixels;
  BlackWhiteAnalyzer::instruction instructionDirection;

  GrassAnalyzer grassAnalyzer;
  image = grassAnalyzer.find_line(image);
  Image::show("Ycbcr", image.getYcbcrImage());
  //Image::show("Binary", image.getBinaryImage(pixelsToBinary, pixelBinary));
  //Image::show("Foreground", image.getBinaryForegroundImage(pixelsToBinary, pixelBinary));
  //Image::show("Background", image.getBinaryBackgroundImage(pixelsToBinary, pixelBinary, backgroundColor));
  //Image::show("Markers", image.getBinaryMarkersImage(pixelsToBinary, pixelBinary, backgroundColor));
  //Image::show("Watershed", image.getBinaryWatershedSegmenterImage(pixelsToBinary, pixelBinary, backgroundColor));

  cv::Mat blackWhite = image.convertInBlackAndWhiteByStrip(pixelsToBinary, pixelBinary, backgroundColor);
  Image::show("Black and White", blackWhite);

  instructionDirection = analyzer.getInstruction(image, pixelsToBinary, pixelBinary, backgroundColor);

  switch(instructionDirection)
  {
    case BlackWhiteAnalyzer::go_foward:
      std::cout << "move_foward" << std::endl;
      break;
    case BlackWhiteAnalyzer::go_left:
      std::cout << "move_left" << std::endl;
      break;
    case BlackWhiteAnalyzer::go_right:
      std::cout << "move_right" << std::endl;
      break;
    case BlackWhiteAnalyzer::turn_180_left:
      std::cout << "turn_180_left" << std::endl;
  }

  //if(!saveFilePath.empty())
  //{
  //  cv::imwrite(saveFilePath, blackWhite);
  //}

  cv::waitKey(0);

  return 0;
}
