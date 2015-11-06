#include <opencv2/opencv.hpp>
#include <string>
#include "image.hpp"
#include "black_white_analyzer.hpp"

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
  //std::vector< std::vector<int> > matrixPixels;
  BlackWhiteAnalyzer::instruction instructionDirection;

  //Image::show("Original", image.getCvImage());
  //Image::show("Binary", image.getBinaryImage(pixelsToBinary, pixelBinary));
  //Image::show("Foreground", image.getBinaryForegroundImage(pixelsToBinary, pixelBinary));
  //Image::show("Background", image.getBinaryBackgroundImage(pixelsToBinary, pixelBinary, backgroundColor));
  //Image::show("Markers", image.getBinaryMarkersImage(pixelsToBinary, pixelBinary, backgroundColor));
  //Image::show("Watershed", image.getBinaryWatershedSegmenterImage(pixelsToBinary, pixelBinary, backgroundColor));

  //cv::Mat blackWhite = image.convertInBlackAndWhiteByStrip(pixelsToBinary, pixelBinary, backgroundColor);
  //Image::show("Black and White", blackWhite);

  instructionDirection = analyzer.getInstruction(image, pixelsToBinary, pixelBinary, backgroundColor);

  switch(instructionDirection)
  {
    case BlackWhiteAnalyzer::go_foward:
      std::cout << "Ir para frente" << std::endl;
      break;
    case BlackWhiteAnalyzer::go_left:
      std::cout << "Ir para esquerda" << std::endl;
      break;
    case BlackWhiteAnalyzer::go_right:
      std::cout << "Ir para direita" << std::endl;
      break;
    case BlackWhiteAnalyzer::rotate_robot:
      std::cout << "Giro de 180 graus" << std::endl;
      break;
  }

  //if(!saveFilePath.empty())
  //{
  //  cv::imwrite(saveFilePath, blackWhite);
  //}

  cv::waitKey(0);

  return 0;
}
