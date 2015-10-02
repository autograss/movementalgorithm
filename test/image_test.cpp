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
};
