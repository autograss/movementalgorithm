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

#include "image.hpp"

class ImageTest : public CppUnit::TestFixture
{
public:
  static CppUnit::Test *suit()
  {
    CppUnit::TestSuite *suitOfTests = new CppUnit::TestSuite("ImageTest");

    suitOfTests->addTest(new CppUnit::TestCaller<ImageTest>("testInstanceNewImage", &ImageTest::testInstanceNewImage));

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
};
