#include <iostream>
#include "black_white_analyzer.hpp"
#include <vector>

#define PIXELS_ERROR 150
#define MATRIX_DISPLACEMENT_ERROR 20
#define DETECTION_RANGE 10
#define BLACK_PIXELS_ERROR 30


using namespace std;


BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::analyzeMatrixOfPixels (vector<vector<int> > matrix) {

	BlackWhiteAnalyzer::instruction result = generateCommand(matrix);

	if(result == go_foward){
		result =  verifyCenterMatrix(matrix);
	}
	
	return result;
}

BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::generateCommand(vector<vector<int> > matrix) {

	vector<int> distance_from_column_of_reference;
	vector<int> columns;
	int x = 0;
	unsigned int i = 0;
	int collumn_of_reference = -1;
	int counter_of_black_pixels = 0;

		for(unsigned int j=0; j<matrix[0].size()-1; j++) {
			if(matrix[i][j+1] == 255 ){
				if(collumn_of_reference == -1) {
					collumn_of_reference = j;
				}

				distance_from_column_of_reference.push_back(collumn_of_reference - j);
				columns.push_back(j);
				j=0;

				if(i<matrix.size())
					i++;
			} 
			else {
				counter_of_black_pixels++;
			}
			
			if (i == DETECTION_RANGE) {
				//cout<<"Black Pixels: "<<counter_of_black_pixels<<endl;
			}

			if(i == DETECTION_RANGE && counter_of_black_pixels < BLACK_PIXELS_ERROR) {
				return BlackWhiteAnalyzer::rotate_robot;
			}

		    if( (j == matrix[0].size()-2) and (collumn_of_reference == -1) )  {
        		j = 0;
     			i++;
     	    }
		}

		for(unsigned int j = 0 ; j < distance_from_column_of_reference.size(); j++) {
			x += distance_from_column_of_reference[j];
		}



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
