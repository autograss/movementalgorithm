#include <iostream>
#include "black_white_analyzer.hpp"
#include <vector>

#define PIXELS_ERROR 10

using namespace std;


BlackWhiteAnalyzer::instruction BlackWhiteAnalyzer::analyzeMatrixOfPixels (vector<vector<int> > matrix) {

	vector<int> distance_from_column_of_reference;
	vector<int> columns;
	int x = 0;
	unsigned int i = 0;
	int collumn_of_reference = -1;

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

      if( (j == matrix[0].size()-2) and (collumn_of_reference == -1) )
      {
        j = 0;
        i++;
      }
		}

		for(unsigned int j = 0 ; j < distance_from_column_of_reference.size(); j++) {
			x += distance_from_column_of_reference[j];
		}
		// cout<<"X: "<<x<<endl;

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
