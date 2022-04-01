#include <cxxtest/TestSuite.h>

#include "graverunner/Jack.hpp"

class JackTestSuite : public CxxTest::TestSuite
{
public:
  void testStartUp()
  {
    {
      Jack jack;
      jack.startUp(101, 23, 30, 40);
      TS_ASSERT_EQUALS(jack.x(), 101);
      TS_ASSERT_EQUALS(jack.y(), 23);
      TS_ASSERT_EQUALS(jack.getWidth(), 30);
      TS_ASSERT_EQUALS(jack.getHeight(), 40);
      TS_ASSERT(jack.isAlive());
    }
    {
      Jack jack;
      jack.startUp(10, 100, 30, 40);
      TS_ASSERT_EQUALS(jack.x(), 10);
      TS_ASSERT_EQUALS(jack.y(), 100);
      TS_ASSERT_EQUALS(jack.getWidth(), 30);
      TS_ASSERT_EQUALS(jack.getHeight(), 40);
      TS_ASSERT(jack.isAlive());
    }
  }
};
