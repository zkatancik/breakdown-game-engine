#include <cxxtest/TestSuite.h>

#include "base/PhysicsManager.hpp"
#include "custom/LevelData.hpp"
#include "custom/Rock.hpp"
#include "custom/Tag.hpp"
#include "custom/TdLevel.hpp"

/**
 * @brief Test suite for Tower Defense rocks.
 */
class RockTestSuite : public CxxTest::TestSuite {
  const float EPSILON = 0.0001f;

 public:
  static RockTestSuite* createSuite() {
    auto suite = new RockTestSuite();
    return suite;
  }

  static void destroySuite(RockTestSuite* suite) {}

  void setUp() { PhysicsManager::getInstance().startUp(); }

  void tearDown() { PhysicsManager::getInstance().shutDown(); }

  /**
   * @brief Tests that rock objects are constructed as expected.
   */
  void testConstruct() {
    TdLevel lvl(200, 100, 1);
    float expectedX = 30.0;
    float expectedY = 101.1;
    float expectedW = 20;
    float expectedH = 22;
    float expectedDx = 13;
    float expectedDy = 17.7;
    Rock rock(lvl, expectedX, expectedY, expectedW, expectedH, expectedDx,
              expectedDy);

    TS_ASSERT_DELTA(rock.x(), expectedX, EPSILON);
    TS_ASSERT_DELTA(rock.y(), expectedY, EPSILON);
    TS_ASSERT_EQUALS(rock.tag(), TdBulletTag);
  }

  /**
   * @brief Test that velocity of a rock is constant over time (ie. when update
   * is called multiple times).
   */
  void testVelocityIsConstant() {
    TdLevel lvl(200, 100, 1);
    float expectedX = 30.0;
    float expectedY = 101.1;
    float expectedW = 20;
    float expectedH = 22;
    float expectedDx = 13;
    float scaledDx = expectedDx * PhysicsManager::GAME_TO_PHYSICS_SCALE;
    float expectedDy = 17.7;
    float scaledDy = expectedDy * PhysicsManager::GAME_TO_PHYSICS_SCALE;
    Rock rock(lvl, expectedX, expectedY, expectedW, expectedH, expectedDx,
              expectedDy);
    rock.update();

    TS_ASSERT_DELTA(rock.x(), expectedX, EPSILON);
    TS_ASSERT_DELTA(rock.y(), expectedY, EPSILON);
    const auto& physComp = rock.physicsComponent();
    TS_ASSERT_DELTA(physComp->vx(), scaledDx, EPSILON);
    TS_ASSERT_DELTA(physComp->vy(), scaledDy, EPSILON);
    TS_ASSERT_EQUALS(rock.tag(), TdBulletTag);

    rock.update();
    TS_ASSERT_DELTA(physComp->vx(), scaledDx, EPSILON);
    TS_ASSERT_DELTA(physComp->vy(), scaledDy, EPSILON);

    rock.update();
    TS_ASSERT_DELTA(physComp->vx(), scaledDx, EPSILON);
    TS_ASSERT_DELTA(physComp->vy(), scaledDy, EPSILON);
  }
};
