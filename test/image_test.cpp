#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

#include <opencv2/opencv.hpp>
#include <vector>
#include "image.hpp"

class ImageTest : public CppUnit::TestFixture
{
public:
  static CppUnit::Test *suit()
  {
    CppUnit::TestSuite *suitOfTests = new CppUnit::TestSuite("ImageTest");

    suitOfTests->addTest(new CppUnit::TestCaller<ImageTest>("testInstanceNewImage", &ImageTest::testInstanceNewImage));
    suitOfTests->addTest(new CppUnit::TestCaller<ImageTest>("testLoadImage", &ImageTest::testLoadImage));
    suitOfTests->addTest(new CppUnit::TestCaller<ImageTest>("testBinaryImage", &ImageTest::testBinaryImage));
    suitOfTests->addTest(new CppUnit::TestCaller<ImageTest>("testBinaryForegroundImage", &ImageTest::testBinaryForegroundImage));
    suitOfTests->addTest(new CppUnit::TestCaller<ImageTest>("testBinaryBackgroundImage", &ImageTest::testBinaryBackgroundImage));
    suitOfTests->addTest(new CppUnit::TestCaller<ImageTest>("testBinaryMarkersImage", &ImageTest::testBinaryMarkersImage));
    suitOfTests->addTest(new CppUnit::TestCaller<ImageTest>("testBinaryWatershedSegmenterImage", &ImageTest::testBinaryWatershedSegmenterImage));
    suitOfTests->addTest(new CppUnit::TestCaller<ImageTest>("testGetPixelMatrix", &ImageTest::testGetPixelMatrix));

    return suitOfTests;
  }

  void testInstanceNewImage()
  {
    Image *image = new Image("test/images/grass_test_01.png");

    CPPUNIT_ASSERT(image != NULL);
  }

  void testLoadImage()
  {
    Image image("test/images/grass_test_01.png");

    CPPUNIT_ASSERT(image.getWidth() == 550);
    CPPUNIT_ASSERT(image.getHeight() == 177);
  }

  void testBinaryImage()
  {
    Image image("test/images/grass_test_01.png");

    cv::Mat binaryImage = image.getBinaryImage(100, 255);

    for(int row = 0; row < binaryImage.rows; row++)
    {
      for(int col = 0; col < binaryImage.row(row).cols; col++)
      {
        float pixelValue = (float)binaryImage.at<uchar>(row, col);
        CPPUNIT_ASSERT( (pixelValue == 0) || (pixelValue == 255) );
      }
    }
  }

  void testBinaryForegroundImage()
  {
    Image image("test/images/grass_test_01.png");

    cv::Mat binaryForegroundImage = image.getBinaryForegroundImage(100, 255);

    for(int row = 0; row < binaryForegroundImage.rows; row++)
    {
      for(int col = 0; col < binaryForegroundImage.row(row).cols; col++)
      {
        float pixelValue = (float)binaryForegroundImage.at<uchar>(row, col);
        CPPUNIT_ASSERT( (pixelValue == 0) || (pixelValue == 255) );
      }
    }
  }

  void testBinaryBackgroundImage()
  {
    int backgroundColor = 125;
    Image image("test/images/grass_test_01.png");

    cv::Mat binaryBackgroundImage = image.getBinaryBackgroundImage(100, 255, backgroundColor);

    for(int row = 0; row < binaryBackgroundImage.rows; row++)
    {
      for(int col = 0; col < binaryBackgroundImage.row(row).cols; col++)
      {
        float pixelValue = (float)binaryBackgroundImage.at<uchar>(row, col);
        CPPUNIT_ASSERT( (pixelValue == 0) || (pixelValue == backgroundColor) );
      }
    }
  }

  void testBinaryMarkersImage()
  {
    int backgroundColor = 125;
    Image image("test/images/grass_test_01.png");

    cv::Mat binaryMarkersImage = image.getBinaryMarkersImage(100, 255, backgroundColor);

    for(int row = 0; row < binaryMarkersImage.rows; row++)
    {
      for(int col = 0; col < binaryMarkersImage.row(row).cols; col++)
      {
        float pixelValue = (float)binaryMarkersImage.at<uchar>(row, col);
        CPPUNIT_ASSERT( (pixelValue == 0) || (pixelValue == 255) || (pixelValue == backgroundColor) );
      }
    }
  }

  void testBinaryWatershedSegmenterImage()
  {
    int backgroundColor = 125;
    Image image("test/images/grass_test_01.png");

    cv::Mat binaryWatershedSegmenterImage = image.getBinaryWatershedSegmenterImage(100, 255, backgroundColor);

    for(int row = 0; row < binaryWatershedSegmenterImage.rows; row++)
    {
      for(int col = 0; col < binaryWatershedSegmenterImage.row(row).cols; col++)
      {
        float pixelValue = (float)binaryWatershedSegmenterImage.at<uchar>(row, col);
        CPPUNIT_ASSERT( (pixelValue == 0) || (pixelValue == 255) || (pixelValue == backgroundColor) );
      }
    }
  }

  void testGetPixelMatrix()
  {
    Image image("test/images/grass_test_01.png");

    cv::Mat binaryImage = image.getBinaryImage(100, 255);
    std::vector< std::vector<int> > pixelMatrix = Image::getPixelMatrix(binaryImage);

    for(unsigned int row = 0; row < pixelMatrix.size(); row++)
    {
      for(unsigned int col = 0; col < pixelMatrix[row].size(); col++)
      {
        int pixelValue = pixelMatrix[row][col];
        CPPUNIT_ASSERT( (pixelValue == 0) || (pixelValue == 255) );
      }
    }
  }
};
