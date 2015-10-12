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

#include <iostream>
#include "node_test.cpp"
#include "image_test.cpp"
#include "black_white_analyzer_test.cpp"


int main()
{
  CppUnit::TextUi::TestRunner runner;

  runner.addTest(NodeTest::suit());
  runner.addTest(BlackWhiteAnalyzerTest::suit());

  bool wasSucessful = !runner.run();

  return wasSucessful;
}

