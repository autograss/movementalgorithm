#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>


bool isWhitePixel(uchar *ptr, int j);
float matMeanRow(const cv::Mat &mat, int row, int indexBegin, int numberElements);
void printLeftBlack(cv::Mat &mat, int row, int col);
void convertImageIntoBlackAndWhite(cv::Mat &grayscaleMat);
void convertImageIntoBlackAndWhite2(cv::Mat &grayscaleMat);


int main(int argc, char** argv )
{
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0] << " <image_path>" << std::endl;
    return -1;
  }

  //Our color image
  cv::Mat imageMat = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  if (imageMat.empty())
  {
          std::cerr << "ERROR: Could not read image " << argv[1] << std::endl;
          return 1;
  }

  //Grayscale matrix
  cv::Mat grayscaleMat (imageMat.size(), CV_8U);

  //Convert BGR to Gray
  cv::cvtColor(imageMat, grayscaleMat, CV_BGR2GRAY);

  //Binary image
  cv::Mat binaryMat(grayscaleMat.size(), grayscaleMat.type());

  //Apply thresholding
  cv::threshold(grayscaleMat, binaryMat, 125, 255, cv::THRESH_BINARY);

  std::cout << "M[0] = " << std::endl << grayscaleMat.row(0) << std::endl << std::endl;
  std::cout << "M width = " << grayscaleMat.cols << std::endl;

  //convertImageIntoBlackAndWhite(grayscaleMat);
  //convertImageIntoBlackAndWhite(binaryMat);

  //Show the results
  cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
  cv::imshow("Output", binaryMat);

  cv::waitKey(0);
  return 0;
}


bool isWhitePixel(uchar *ptr, int j)
{
  return ptr[3*j+2] > 200 and ptr[3*j+1] > 200 and ptr[3*j+0] > 200;
}


float matMeanRow(const cv::Mat &mat, int row, int indexBegin, int numberElements)
{
  float sum = 0;

  for(int i = indexBegin; i < (indexBegin + numberElements); i++)
  {
    sum += (float)mat.at<uchar>(row, i);
  }

  return sum / numberElements;
}

float matrixMeanCol(const std::vector< std::vector<float> > &matrix, int row, int col, int indexBegin, int numberElements)
{
  float sum = 0;

  for(int i = indexBegin; i < (indexBegin + numberElements); i++)
  {
    sum += matrix[row][i];
  }

  return sum / numberElements;
}


void printLeftBlack(cv::Mat &mat, int row, int col)
{
  for(int i = 0; i < col; i++)
  {
    //std::cout << "i: " << i << "; pixel: " <<  mat.row(row).col(i) << std::endl;
    mat.row(row).col(i) = 0.0f;
  }
  for(int i = col; i < mat.row(row).cols; i++)
  {
    mat.row(row).col(i) = 255.0f;
  }
}


void convertImageIntoBlackAndWhite(cv::Mat &grayscaleMat)
{
  int scale = 20;
  float prevMean = 0, mean = 0, deltaMean = 20.0f;

  for(int row = 0; row < grayscaleMat.rows; row++)
  {
    for(int i = 0; (i*scale) + (scale / 2) < grayscaleMat.row(row).cols; i++)
    {
      if(i == 0)
        prevMean = mean;
      else
        prevMean = (prevMean + mean) / 2.0f;

      mean = matMeanRow(grayscaleMat, row, i * scale, scale);

      //std::cout << "mean[" << i*scale << "] = " << matMeanRow(grayscaleMat, row, i * scale, scale) << std::endl;

      if(abs(mean - prevMean) >= deltaMean)
      {
        int col = (i*scale) + (scale / 2);
        //std::cout << "AQUI: " << col << std::endl;
        printLeftBlack(grayscaleMat, row, col);
        break;
      }
    }
  }
}

void convertImageIntoBlackAndWhite2(cv::Mat &grayscaleMat)
{
  int scale = 20;
  float mean = 0.0f;
  std::vector< std::vector<float> > matrixMean;

  for(int row = 0; row < grayscaleMat.rows; row++)
  {
    std::vector<float> vectorMean;
    for(int i = 0; (i*scale) + (scale / 2) < grayscaleMat.row(row).cols; i++)
    {
      mean = matMeanRow(grayscaleMat, row, i * scale, scale);
      vectorMean.push_back(mean);
      //std::cout << "mean[" << i*scale << "] = " << matMeanRow(grayscaleMat, row, i * scale, scale) << std::endl;
    }
    matrixMean.push_back(vectorMean);
  }


  std::vector< std::vector<float> > fMatrixMean;
  for(unsigned int i = 0; (i*scale) + (scale / 2) < matrixMean.size(); i++)
  {
    std::vector<float> fVectorMean;

    for(unsigned int j = 0; j < fMatrixMean[i].size(); j++)
    {
    }
  }

}





















