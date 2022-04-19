#include <cxxtest/TestSuite.h>

#include "base/PhysicsManager.hpp"
#include "breakout/BreakoutGameLevel.hpp"
#include "breakout/Paddle.hpp"
#include "breakout/Tag.hpp"

class PaddleTestSuite : public CxxTest::TestSuite {
  const float EPSILON = 0.0001f;

 public:
  static PaddleTestSuite* createSuite() {
    auto suite = new PaddleTestSuite();
    return suite;
  }

  static void destroySuite(PaddleTestSuite* suite) {}

  void setUp() { PhysicsManager::getInstance().startUp(); }

  void tearDown() { PhysicsManager::getInstance().shutDown(); }

  void testConstruct() {
    BreakoutGameLevel lvl(200, 100, BreakoutGameLevel::GameDifficulty::Medium,
                          0);
    float expectedWidth = 48;
    float expectedX = lvl.w() / 2 - (expectedWidth / 2);
    float expectedY = lvl.h() - 50;
    Paddle paddle(lvl, lvl.w(), lvl.h(), expectedWidth, 10);

    const auto& physComp = paddle.physicsComponent();
    TS_ASSERT_DELTA(paddle.x(), expectedX, EPSILON);
    TS_ASSERT_DELTA(paddle.y(), expectedY, EPSILON);
    // Velocities should be zero, change when user presses an arrow key
    TS_ASSERT_DELTA(physComp->vx(), 0.0f, EPSILON);
    TS_ASSERT_DELTA(physComp->vy(), 0.0f, EPSILON);
    TS_ASSERT_EQUALS(paddle.tag(), BreakoutPaddleTag);
  }
};
