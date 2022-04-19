#include <cxxtest/TestSuite.h>

#include "base/PhysicsManager.hpp"
#include "custom/LevelData.hpp"
#include "custom/Tag.hpp"
#include "custom/TdBlock.hpp"
#include "custom/TdLevel.hpp"

/**
 * @brief Test suite for Tower Defense blocks.
 */
class BlockTestSuite : public CxxTest::TestSuite {
  const float EPSILON = 0.0001f;

 public:
  static BlockTestSuite* createSuite() {
    auto suite = new BlockTestSuite();
    return suite;
  }

  static void destroySuite(BlockTestSuite* suite) {}

  void setUp() { PhysicsManager::getInstance().startUp(); }

  void tearDown() { PhysicsManager::getInstance().shutDown(); }

  /**
   * @brief Tests constructing a plain block.
   */
  void testConstructBasic() {
    TdLevel lvl(200, 100, 1);
    TdBlockData expectedBd{TdLevelItem::PLAINBLOCK, "A", false};
    float expectedX = 30.0;
    float expectedY = 101.1;
    int expectedW = 34;
    int expectedH = 10;
    TdBlock block(lvl, expectedX, expectedY, expectedBd,
                  {expectedW, expectedH});

    TS_ASSERT_DELTA(block.x(), expectedX, EPSILON);
    TS_ASSERT_DELTA(block.y(), expectedY, EPSILON);
    TS_ASSERT_EQUALS(block.w(), expectedW);
    TS_ASSERT_EQUALS(block.h(), expectedH);
    const auto& physComp = block.physicsComponent();
    TS_ASSERT_DELTA(physComp->vx(), 0.0, EPSILON);
    TS_ASSERT_DELTA(physComp->vy(), 0.0, EPSILON);
    TS_ASSERT_EQUALS(block.tag(), TdBlockTag);
  }

  /**
   * @brief Tests constructing another type (Start) of block.
   */
  void testConstructStart() {
    TdLevel lvl(200, 100, 1);
    TdBlockData expectedBd{TdLevelItem::START, "S", true};
    float expectedX = 30.0;
    float expectedY = 101.1;
    int expectedW = 11;
    int expectedH = 44;
    TdBlock block(lvl, expectedX, expectedY, expectedBd,
                  {expectedW, expectedH});

    TS_ASSERT_DELTA(block.x(), expectedX, EPSILON);
    TS_ASSERT_DELTA(block.y(), expectedY, EPSILON);
    TS_ASSERT_EQUALS(block.w(), expectedW);
    TS_ASSERT_EQUALS(block.h(), expectedH);
    const auto& physComp = block.physicsComponent();
    TS_ASSERT_DELTA(physComp->vx(), 0.0, EPSILON);
    TS_ASSERT_DELTA(physComp->vy(), 0.0, EPSILON);
    TS_ASSERT_EQUALS(block.tag(), TdBlockTag);
  }

  /**
   * @brief Tests that the block's tag can be overridden, e.g. to act as the end
   * block.
   */
  void testConstructOverrideTag() {
    TdLevel lvl(200, 100, 1);
    TdBlockData expectedBd{TdLevelItem::START, "S", true};
    float expectedX = 30.0;
    float expectedY = 101.1;
    int expectedW = 20;
    int expectedH = 22;
    TdBlock block(lvl, expectedX, expectedY, expectedBd, {expectedW, expectedH},
                  TdEndBlockTag);

    TS_ASSERT_DELTA(block.x(), expectedX, EPSILON);
    TS_ASSERT_DELTA(block.y(), expectedY, EPSILON);
    TS_ASSERT_EQUALS(block.w(), expectedW);
    TS_ASSERT_EQUALS(block.h(), expectedH);
    const auto& physComp = block.physicsComponent();
    TS_ASSERT_DELTA(physComp->vx(), 0.0, EPSILON);
    TS_ASSERT_DELTA(physComp->vy(), 0.0, EPSILON);
    TS_ASSERT_EQUALS(block.tag(), TdEndBlockTag);
  }
};
