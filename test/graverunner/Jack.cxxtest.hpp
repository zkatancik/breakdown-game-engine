#include <cxxtest/TestSuite.h>

#include "graverunner/Jack.hpp"
#include "graverunner/GraveRunnerLevel.hpp"

class JackTestSuite : public CxxTest::TestSuite
{
public:
  void testConstruct()
  {
    {
      GraveRunnerLevel lvl(1000, 500, 1);
      Jack jack(lvl, 101, 23, 30, 40);
      TS_ASSERT_EQUALS(jack.x(), 101);
      TS_ASSERT_EQUALS(jack.y(), 23);
      TS_ASSERT_EQUALS(jack.w(), 30);
      TS_ASSERT_EQUALS(jack.h(), 40);
      TS_ASSERT(jack.isAlive());
      TS_ASSERT_EQUALS(jack.GetNumCollectedKeys(), 0);
    }
    {
      GraveRunnerLevel lvl(1000, 500, 2);
      Jack jack(lvl, 10, 100, 30, 40);
      TS_ASSERT_EQUALS(jack.x(), 10);
      TS_ASSERT_EQUALS(jack.y(), 100);
      TS_ASSERT_EQUALS(jack.w(), 30);
      TS_ASSERT_EQUALS(jack.h(), 40);
      TS_ASSERT(jack.isAlive());
      TS_ASSERT_EQUALS(jack.GetNumCollectedKeys(), 0);
    }
  }
};
