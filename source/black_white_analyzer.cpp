#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
#include "black_white_analyzer.hpp"

#define PIXELS_ERROR 10
#define MATRIX_DISPLACEMENT_ERROR 20
#define BORDER_DOWN_AVERAGE_PIXELS_ERROR 5

BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::analyzeMatrixOfPixels (std::vector<std::vector<int> > matrix) {

	result = generateCommand(matrix);

	if(result == go_foward){
		result =  verifyCenterMatrix(matrix);
	}

	result = verifyTurn180(matrix);

	return result;
}



BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::verifyTurn180(std::vector<std::vector<int> > matrix) {
  int borderDown = -1;
  std::vector<int> distanceFromBorderDown;
  unsigned int i = 0;

  for(unsigned int j = 0; j < matrix[i].size()/4; j++)
  {

	    for(i = 0; i < matrix.size() - 10; i++)
	    {

	      if(matrix[i][j] == 255 && matrix[i+1][j] == 0){

		if(borderDown == -1)
	       	{
	 	   borderDown = i;
		}
		else
		{
		   distanceFromBorderDown.push_back(i);
		}
	     }

	   }
  }
  double sum = std::accumulate(distanceFromBorderDown.begin(),distanceFromBorderDown.end(),0.0);
  double mean = sum/distanceFromBorderDown.size();

  if (mean < (borderDown+BORDER_DOWN_AVERAGE_PIXELS_ERROR)) {
	return BlackWhiteAnalyzer::turn_180_left;
  }
  else {

 	return result;
  }

}

BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::generateCommand(std::vector< std::vector<int> > matrix) {
  int diferenceResult = 255;
  std::vector<int> vectorX;
  std::vector<int> vectorY;

  //std::cout << "Diference: " << std::endl;
  for(unsigned int i = 1; i < matrix.size(); i++)
  {
    for(unsigned int j = 1; j < matrix.size(); j++) {
      //std::cout << (matrix[i][j] - matrix[i][j-1]) << ", ";
      if(matrix[i][j] - matrix[i][j-1] == diferenceResult)
      {
        vectorX.push_back(i);
        vectorY.push_back(j);
      }
    }
  }

  //std::cout << "=================" << std::endl;

  double slopeLine = slope(vectorX, vectorY);

  //std::cout << "slopeLine: " << slopeLine << std::endl;

  if(abs(slopeLine) > 8.0)
  {
    return BlackWhiteAnalyzer::go_foward;
  }
  else if (slopeLine > 0.0)
  {
    return BlackWhiteAnalyzer::go_left;
  }
  else
  {
    return BlackWhiteAnalyzer::go_right;
  }
}


BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::verifyCenterMatrix(std::vector< std::vector<int> > matrix) {

	unsigned int number_of_collumns = matrix[0].size();
	unsigned int number_of_lines = matrix.size();
	unsigned int count_before_line = 0;
	unsigned int count_after_line = 0;
	bool before_the_middle = true;
	unsigned int i = 0;

	for(unsigned int j=0; j<number_of_collumns - 1; j++) {


		if(before_the_middle)
			count_before_line++;

		if(before_the_middle == false && matrix[0][j] == 0) {
			count_after_line++;
		}

		if(matrix[0][j+1] != 0 ){
			before_the_middle = false;
		}

		if (j == number_of_collumns - 2 && i < number_of_lines - 1) {
			i++;
			j = 0;
		}
	}

	float x = count_before_line - count_after_line;
//	cout<<"Before Line: "<<count_before_line<<endl;
//	cout<<"After Line: "<<count_after_line<<endl;
//	cout<<"X: "<<x<<endl;

	if (x < -MATRIX_DISPLACEMENT_ERROR){
			return BlackWhiteAnalyzer::go_left;
	}

	else if (count_after_line == 0) {
		return BlackWhiteAnalyzer::go_foward;
	}

	else if (x == 0 || (x > -MATRIX_DISPLACEMENT_ERROR && x < MATRIX_DISPLACEMENT_ERROR)) {
		return BlackWhiteAnalyzer::go_foward;
	}
	else if (x > MATRIX_DISPLACEMENT_ERROR) {
		return BlackWhiteAnalyzer::go_right;
	}

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

double
BlackWhiteAnalyzer::slope(const std::vector<int>& x, const std::vector<int>& y) {
    const auto n = x.size();
    const auto s_x = std::accumulate(x.begin(), x.end(), 0.0);
    const auto s_y = std::accumulate(y.begin(), y.end(), 0.0);
    const auto s_xx = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
    const auto s_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
    const auto numerator = (n * s_xx - s_x * s_x);
    const auto denominator = (n * s_xy - s_x * s_y);

    //std::cout << "n: " << n << std::endl;
    //std::cout << "s_x: " << s_x << std::endl;
    //std::cout << "s_y: " << s_y << std::endl;
    //std::cout << "s_xx: " << s_xx << std::endl;
    //std::cout << "s_xy: " << s_xy << std::endl;
    //std::cout << "numerator: " << numerator << std::endl;
    //std::cout << "denominator: " << denominator << std::endl;

    if(denominator == 0)
    {
      return 0.0;
    }

    return numerator / denominator;
}

