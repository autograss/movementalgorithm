#include <iostream>
#include "black_white_analyzer.hpp"
#include <vector>

#define PIXELS_ERROR 10
#define MATRIX_DISPLACEMENT_ERROR 20
#define BORDER_DOWN_AVERAGE_PIXELS_ERROR 5

using namespace std;


BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::analyzeMatrixOfPixels (vector<vector<int> > matrix) {

	result = generateCommand(matrix);

	if(result == go_foward){
		result =  verifyCenterMatrix(matrix);
	}

	result = verifyTurn180(matrix);

	return result;
}



BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::verifyTurn180(vector<vector<int> > matrix) {


  int borderDown = -1;
  vector<int> distanceFromBorderDown;
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
  double sum = accumulate(distanceFromBorderDown.begin(),distanceFromBorderDown.end(),0.0);
  double mean = sum/distanceFromBorderDown.size();

  if (mean < (borderDown+BORDER_DOWN_AVERAGE_PIXELS_ERROR)) {
	return BlackWhiteAnalyzer::turn_180_left;	
  }
  else {

 	return result;
  }

}


BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::generateCommand(vector<vector<int> > matrix) {
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

  return BlackWhiteAnalyzer::go_foward;


}


BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::verifyCenterMatrix(vector<vector<int> > matrix) {

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
