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

#include "node.hpp"

using namespace std;

class NodeTest : public CppUnit::TestFixture
{
public:
  static CppUnit::Test *suit()
  {
    CppUnit::TestSuite *suitOfTests = new CppUnit::TestSuite("NodeTest");

    suitOfTests->addTest(new CppUnit::TestCaller<NodeTest>("testInstanceNewNode", &NodeTest::testInstanceNewNode));
    suitOfTests->addTest(new CppUnit::TestCaller<NodeTest>("testAddNode", &NodeTest::testAddNode));

    return suitOfTests;
  }

  void testInstanceNewNode()
  {
    Node *node = new Node(10);

    CPPUNIT_ASSERT(node->value == 10);
  }

  void testAddNode()
  {
    Node *nodeOne = new Node(10);
    Node *nodeTwo = new Node(20);

    nodeOne->next = nodeTwo;
    nodeTwo->prev = nodeOne;

    CPPUNIT_ASSERT(nodeOne->next == nodeTwo);
    CPPUNIT_ASSERT(nodeTwo->prev == nodeOne);
  }
};
