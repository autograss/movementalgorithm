#include <opencv/cv.hpp>
#include <stdio.h>
#include <iostream>
#include "image.hpp"
#include "grass_analyzer.hpp"

using namespace std;

void GrassAnalyzer::find_line(Image image)
{

    cv::cvtColor(image.getCvImage(), image.getCvImage(), CV_GRAY2BGR);

}
