#include <cxxtest/TestSuite.h>

#include <chrono>
#include <thread>

#include "base/PhysicsManager.hpp"
#include "custom/CustomEnemy.hpp"
#include "custom/LevelData.hpp"
#include "custom/PeriodicRockThrowComponent.hpp"
#include "custom/Rock.hpp"
#include "custom/Tag.hpp"
#include "custom/TdLevel.hpp"

/**
 * @brief Test suite for Tower Defense PeriodicRockThrowComponents.
 */
class PeriodicRockThrowComponentTestSuite : public CxxTest::TestSuite {
  const float EPSILON = 0.0001f;

 public:
  static PeriodicRockThrowComponentTestSuite* createSuite() {
    auto suite = new PeriodicRockThrowComponentTestSuite();
    return suite;
  }

  static void destroySuite(PeriodicRockThrowComponentTestSuite* suite) {}

  void setUp() { PhysicsManager::getInstance().startUp(); }

  void tearDown() { PhysicsManager::getInstance().shutDown(); }

  /**
   * @brief Helper that counts the number of times objects with a particular tag
   * occur in the level.
   *
   * @param level level to search
   * @param tag tag to search for
   * @return int the count
   */
  int numTagInLevel(const Level& level, int tag) {
    int count = 0;
    for (const auto& obj : level.getGameObjects()) {
      if (obj->tag() == tag) {
        count++;
      }
    }
    return count;
  }

  /**
   * @brief Does any object in the level have this tag?
   *
   * @param level level to search
   * @param tag tag to search for
   * @return true/false
   */
  bool anyTagInLevel(const Level& level, int tag) {
    return numTagInLevel(level, tag) > 0;
  }

  /**
   * @brief Tests that if there is an enemy in range, the component will fire a
   * rock. The cooldown is long (2 mins), so it won't fire another.
   */
  void testEnemyInRangeLongCooldown() {
    TdLevel lvl(200, 100, 1);

    std::shared_ptr<GameObject> tower = std::make_shared<GameObject>(
        lvl, 20, 20, 10, 10, TdRockThrowerTowerTag);
    std::shared_ptr<PeriodicRockThrowComponent> componentUnderTest =
        std::make_shared<PeriodicRockThrowComponent>(*tower, 40, 4, 120000);
    tower->addGenericComponent(componentUnderTest);
    lvl.addObject(tower);

    std::shared_ptr<CustomEnemy> enemy = std::make_shared<CustomEnemy>(
        lvl, 35, 20, 20, 10, TdLevelItem::HELMETOGRE, 100, [&]() {});
    lvl.addObject(enemy);

    // Initial update to setup the objects
    lvl.update();

    TS_ASSERT(anyTagInLevel(lvl, TdRockThrowerTowerTag));
    TS_ASSERT(anyTagInLevel(lvl, TdEnemyTag));
    TS_ASSERT(!anyTagInLevel(lvl, TdBulletTag));

    // Update each object, means tower should fire a rock
    lvl.update();

    TS_ASSERT(anyTagInLevel(lvl, TdRockThrowerTowerTag));
    TS_ASSERT(anyTagInLevel(lvl, TdEnemyTag));
    TS_ASSERT_EQUALS(numTagInLevel(lvl, TdBulletTag), 1);

    // Long cooldown time, so shouldn't fire again
    lvl.update();

    TS_ASSERT(anyTagInLevel(lvl, TdRockThrowerTowerTag));
    TS_ASSERT(anyTagInLevel(lvl, TdEnemyTag));
    TS_ASSERT_EQUALS(numTagInLevel(lvl, TdBulletTag), 1);
  }

  /**
   * @brief Tests that if there is an enemy in range, the component will fire a
   * rock. The cooldown time is set to 0 ticks so it should fire another when
   * updated again.
   */
  void testEnemyInRangeNoCooldown() {
    TdLevel lvl(200, 100, 1);

    std::shared_ptr<GameObject> tower = std::make_shared<GameObject>(
        lvl, 20, 20, 10, 10, TdRockThrowerTowerTag);
    std::shared_ptr<PeriodicRockThrowComponent> componentUnderTest =
        std::make_shared<PeriodicRockThrowComponent>(*tower, 40, 4, 0);
    tower->addGenericComponent(componentUnderTest);
    lvl.addObject(tower);

    std::shared_ptr<CustomEnemy> enemy = std::make_shared<CustomEnemy>(
        lvl, 35, 20, 20, 10, TdLevelItem::HELMETOGRE, 100, [&]() {});
    lvl.addObject(enemy);

    // Initial update to setup the objects
    lvl.update();

    TS_ASSERT(anyTagInLevel(lvl, TdRockThrowerTowerTag));
    TS_ASSERT(anyTagInLevel(lvl, TdEnemyTag));
    TS_ASSERT(!anyTagInLevel(lvl, TdBulletTag));

    // Update each object, means tower should fire a rock
    lvl.update();

    TS_ASSERT(anyTagInLevel(lvl, TdRockThrowerTowerTag));
    TS_ASSERT(anyTagInLevel(lvl, TdEnemyTag));
    TS_ASSERT_EQUALS(numTagInLevel(lvl, TdBulletTag), 1);

    // Cooldown of zero so calling update should fire another rock (and the 1st
    // rock hasn't reached target yet)
    lvl.update();

    TS_ASSERT(anyTagInLevel(lvl, TdRockThrowerTowerTag));
    TS_ASSERT(anyTagInLevel(lvl, TdEnemyTag));
    TS_ASSERT_EQUALS(numTagInLevel(lvl, TdBulletTag), 2);
  }

  /**
   * @brief Tests that if there is no enemy in range, the component does not
   * fire rocks even on multiple attempts.
   */
  void testEnemyOutOfRange() {
    TdLevel lvl(200, 100, 1);

    std::shared_ptr<GameObject> tower = std::make_shared<GameObject>(
        lvl, 20, 20, 10, 10, TdRockThrowerTowerTag);
    std::shared_ptr<PeriodicRockThrowComponent> componentUnderTest =
        std::make_shared<PeriodicRockThrowComponent>(*tower, 40, 4, 120000);
    tower->addGenericComponent(componentUnderTest);
    lvl.addObject(tower);

    std::shared_ptr<CustomEnemy> enemy = std::make_shared<CustomEnemy>(
        lvl, 150, 70, 20, 10, TdLevelItem::HELMETOGRE, 100, [&]() {});
    lvl.addObject(enemy);

    // Initial update to setup the objects
    lvl.update();

    TS_ASSERT(anyTagInLevel(lvl, TdRockThrowerTowerTag));
    TS_ASSERT(anyTagInLevel(lvl, TdEnemyTag));
    TS_ASSERT(!anyTagInLevel(lvl, TdBulletTag));

    // Update each object, tower should not fire rock
    lvl.update();

    TS_ASSERT(anyTagInLevel(lvl, TdRockThrowerTowerTag));
    TS_ASSERT(anyTagInLevel(lvl, TdEnemyTag));
    TS_ASSERT(!anyTagInLevel(lvl, TdBulletTag));

    // Update each object, tower should still not fire rock
    lvl.update();

    TS_ASSERT(anyTagInLevel(lvl, TdRockThrowerTowerTag));
    TS_ASSERT(anyTagInLevel(lvl, TdEnemyTag));
    TS_ASSERT(!anyTagInLevel(lvl, TdBulletTag));
  }
};
