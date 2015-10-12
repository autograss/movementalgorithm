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
#include "black_white_analyzer.hpp"

#include <iostream>

class BlackWhiteAnalyzerTest : public CppUnit::TestFixture
{
public:
  static CppUnit::Test *suit()
  {
    CppUnit::TestSuite *suitOfTests = new CppUnit::TestSuite("BlackWhiteAnalyzerTest");

    suitOfTests->addTest(new CppUnit::TestCaller<BlackWhiteAnalyzerTest>("testGoFoward", &BlackWhiteAnalyzerTest::testGoFoward));
    suitOfTests->addTest(new CppUnit::TestCaller<BlackWhiteAnalyzerTest>("testGoLeftOne", &BlackWhiteAnalyzerTest::testGoLeftOne));
    suitOfTests->addTest(new CppUnit::TestCaller<BlackWhiteAnalyzerTest>("testGoLeftTwo", &BlackWhiteAnalyzerTest::testGoLeftTwo));
    suitOfTests->addTest(new CppUnit::TestCaller<BlackWhiteAnalyzerTest>("testGoRightOne", &BlackWhiteAnalyzerTest::testGoRightOne));
    suitOfTests->addTest(new CppUnit::TestCaller<BlackWhiteAnalyzerTest>("testGoRightTwo", &BlackWhiteAnalyzerTest::testGoRightTwo));

    return suitOfTests;
  }

  void testGoFoward()
  {
    unsigned int pixelBinary = 255;
    unsigned int pixelsToBinary = 100;
    unsigned int backgroundColor = 125;

    BlackWhiteAnalyzer analyzer;
    Image image("test/images/go_foward.jpg");
    BlackWhiteAnalyzer::instruction instruction;

    instruction = analyzer.getInstruction(image, pixelsToBinary, pixelBinary, backgroundColor);

    CPPUNIT_ASSERT(instruction == BlackWhiteAnalyzer::go_foward);
  }

  void testGoLeftOne()
  {
    unsigned int pixelBinary = 255;
    unsigned int pixelsToBinary = 100;
    unsigned int backgroundColor = 125;

    BlackWhiteAnalyzer analyzer;
    Image image("test/images/go_left_01.png");
    BlackWhiteAnalyzer::instruction instruction;

    instruction = analyzer.getInstruction(image, pixelsToBinary, pixelBinary, backgroundColor);

    CPPUNIT_ASSERT(instruction == BlackWhiteAnalyzer::go_left);
  }

  void testGoLeftTwo()
  {
    unsigned int pixelBinary = 255;
    unsigned int pixelsToBinary = 100;
    unsigned int backgroundColor = 125;

    BlackWhiteAnalyzer analyzer;
    Image image("test/images/go_left_02.png");
    BlackWhiteAnalyzer::instruction instruction;

    instruction = analyzer.getInstruction(image, pixelsToBinary, pixelBinary, backgroundColor);

    CPPUNIT_ASSERT(instruction == BlackWhiteAnalyzer::go_left);
  }

  void testGoRightOne()
  {
    unsigned int pixelBinary = 255;
    unsigned int pixelsToBinary = 100;
    unsigned int backgroundColor = 125;

    BlackWhiteAnalyzer analyzer;
    Image image("test/images/go_right_01.png");
    BlackWhiteAnalyzer::instruction instruction;

    instruction = analyzer.getInstruction(image, pixelsToBinary, pixelBinary, backgroundColor);

    CPPUNIT_ASSERT(instruction == BlackWhiteAnalyzer::go_right);
  }

  void testGoRightTwo()
  {
    unsigned int pixelBinary = 255;
    unsigned int pixelsToBinary = 100;
    unsigned int backgroundColor = 125;

    BlackWhiteAnalyzer analyzer;
    Image image("test/images/go_right_02.png");
    BlackWhiteAnalyzer::instruction instruction;

    instruction = analyzer.getInstruction(image, pixelsToBinary, pixelBinary, backgroundColor);

    CPPUNIT_ASSERT(instruction == BlackWhiteAnalyzer::go_right);
  }
};

