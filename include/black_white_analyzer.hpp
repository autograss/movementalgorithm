#ifndef BLACK_WHITE_ANALYZER_H
#define BLACK_WHITE_ANALYZER_H
#include <vector>
#include "image.hpp"

using namespace std;

const int WIDTH_SIZE = 50;
const int HEIGHT_SIZE = 50;

class BlackWhiteAnalyzer
{
  public:
    BlackWhiteAnalyzer(){};

    typedef enum instruction {
    	go_foward = 0,
    	go_left,
    	go_right,
        rotate_robot
    }instruction;

    instruction analyzeMatrixOfPixels (vector<vector<int> >);
    instruction generateCommand (vector<vector<int> >);
    instruction verifyCenterMatrix (vector<vector<int> >);

    instruction getInstruction (Image image, unsigned int pixelsToBinary,
                                unsigned int pixelBinary, unsigned int backgroundColor);

  private:
};
#endif
