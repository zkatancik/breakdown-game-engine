#include <cxxtest/TestSuite.h>

#include "base/PhysicsManager.hpp"
#include "breakout/Ball.hpp"
#include "breakout/BreakoutGameLevel.hpp"
#include "breakout/Tag.hpp"

class BallTestSuite : public CxxTest::TestSuite {
  const float EPSILON = 0.0001f;

 public:
  static BallTestSuite* createSuite() {
    auto suite = new BallTestSuite();
    return suite;
  }

  static void destroySuite(BallTestSuite* suite) {}

  void setUp() { PhysicsManager::getInstance().startUp(); }

  void tearDown() { PhysicsManager::getInstance().shutDown(); }

  void testConstruct() {
    BreakoutGameLevel lvl(200, 100, BreakoutGameLevel::GameDifficulty::Medium,
                          0);
    float expectedX = 30.0;
    float expectedY = 101.1;
    float expectedDx = -8.9;
    float expectedDy = 9.9;
    Ball ball(lvl, expectedX, expectedY, expectedDx, expectedDy);

    const auto& physComp = ball.physicsComponent();
    TS_ASSERT_DELTA(ball.x(), expectedX, EPSILON);
    TS_ASSERT_DELTA(ball.y(), expectedY, EPSILON);
    TS_ASSERT_DELTA(physComp->vx(),
                    expectedDx * PhysicsManager::GAME_TO_PHYSICS_SCALE,
                    EPSILON);
    TS_ASSERT_DELTA(physComp->vy(),
                    expectedDy * PhysicsManager::GAME_TO_PHYSICS_SCALE,
                    EPSILON);
    TS_ASSERT_EQUALS(ball.tag(), BreakoutBallTag);
  }

  void testStop() {
    BreakoutGameLevel lvl(200, 100, BreakoutGameLevel::GameDifficulty::Hard, 1);
    float expectedX = 30.0;
    float expectedY = 101.1;
    float expectedDx = -8.9;
    float expectedDy = 9.9;
    Ball ball(lvl, expectedX, expectedY, expectedDx, expectedDy);

    const auto& physComp = ball.physicsComponent();
    TS_ASSERT_DELTA(ball.x(), expectedX, EPSILON);
    TS_ASSERT_DELTA(ball.y(), expectedY, EPSILON);
    TS_ASSERT_DELTA(physComp->vx(),
                    expectedDx * PhysicsManager::GAME_TO_PHYSICS_SCALE,
                    EPSILON);
    TS_ASSERT_DELTA(physComp->vy(),
                    expectedDy * PhysicsManager::GAME_TO_PHYSICS_SCALE,
                    EPSILON);

    ball.stop();
    TS_ASSERT_DELTA(ball.x(), expectedX, EPSILON);
    TS_ASSERT_DELTA(ball.y(), expectedY, EPSILON);
    TS_ASSERT_DELTA(physComp->vx(), 0.0f, EPSILON);
    TS_ASSERT_DELTA(physComp->vy(), 0.0f, EPSILON);
  }
};
