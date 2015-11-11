#include <iostream>
#include "black_white_analyzer.hpp"
#include <vector>

#define PIXELS_ERROR 10

using namespace std;


BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::analyzeMatrixOfPixels (vector<vector<int> > matrix) {

  int topLeft=-1, topRight=-1, bottomLeft=-1, bottomRight=-1;
  int x;

  for(unsigned int i = 0; i < matrix.size(); i++)
  {
    for(unsigned int j = 0; j < matrix[i].size(); j++)
    {
      if(topLeft == -1)
      {
        if(matrix[i][j] == 255)
          topLeft = j;
      }
      else if(topRight == -1)
      {
        if(matrix[i][j] == 0)
          topRight = j-1;
      }
      else
      {
        break;
      }
    }
  }
  for(int i = matrix.size()-1; i >= 0; i--)
  {
    for(int j = matrix[i].size()-1; j >= 0; j--)
    {
      if(bottomRight == -1)
      {
        if(matrix[i][j] == 255)
          bottomRight = j;
      }
      else if(bottomLeft == -1)
      {
        if(matrix[i][j] == 0)
          bottomLeft = j-1;
      }
      else
      {
        break;
      }
    }
  }

  x = ((topRight + topLeft) / 2) - ((bottomRight + bottomLeft) / 2);

  if (x < -PIXELS_ERROR){
    return BlackWhiteAnalyzer::go_left;
  }
  else if (x == 0 || (x > -PIXELS_ERROR && x < PIXELS_ERROR)) {
    return BlackWhiteAnalyzer::go_foward;
  }
  else if (x > PIXELS_ERROR) {
    return BlackWhiteAnalyzer::go_right;
  }

	// x = columns[0];


	// for(int i=0; i < columns.size(); i++){

	// 	if(x != columns[i]) {
	// 		cout<<"Pixels não alinhados!"<<endl;
	// 		return BlackWhiteAnalyzer::go_left;
	// 	}

	// }

	// cout<<"Pixels alinhados!"<<endl;

	return BlackWhiteAnalyzer::go_foward;
}

BlackWhiteAnalyzer::instruction
BlackWhiteAnalyzer::getInstruction (Image image, unsigned int pixelsToBinary,
                                    unsigned int pixelBinary, unsigned int backgroundColor)
{
    BlackWhiteAnalyzer analyzer;
    std::vector< std::vector<int> > matrixPixels;

    cv::Mat blackWhite = image.convertInBlackAndWhiteByStrip(pixelsToBinary, pixelBinary, backgroundColor);
    matrixPixels = Image::getPixelMatrix(blackWhite);
    return analyzer.analyzeMatrixOfPixels(matrixPixels);
}
