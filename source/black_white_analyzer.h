#ifndef BLACK_WHITE_ANALYZER_H
#define BLACK_WHITE_ANALYZER_H
#include <vector>

using namespace std;

const int WIDTH_SIZE = 50;
const int HEIGHT_SIZE = 50;




class BlackWhiteAnalyzer
{

  public:




    BlackWhiteAnalyzer(){};

    


    typedef enum instruction {
    	go_foward,
    	go_left,
    	go_right
    }instruction;


    instruction analyzeMatrixOfPixels (vector<vector<int> >);

  private:

};    


#endif
