#include <cxxtest/TestSuite.h>

#include "graverunner/Block.hpp"
#include "graverunner/LevelData.hpp"
#include "graverunner/GraveRunnerLevel.hpp"

class BlockTestSuite : public CxxTest::TestSuite {
 public:
  const float EPSILON = 0.001f;

  // --------------------- BLOCK TESTS -----------------------------------

  void testUpdate() {}

  void testRender() {}

  void testGetCenter() {
    {
      GraveRunnerLevel lvl(1000, 500, 1);
      auto data = BlockData();
      data.block_Type = BlockType::PlainBlock;
      data.blockNumber = 1;
      Vector2D<int> blockSize{128, 128};
      Block *block = new Block(lvl, 0, 0, data, blockSize);

      Vector2D<int> expectedCenter{};
      expectedCenter[0] = (blockSize.x / 2);
      expectedCenter[1] = (blockSize.y / 2);
      TS_ASSERT_EQUALS(block->getCenter()[0], expectedCenter[0]);
      TS_ASSERT_EQUALS(block->getCenter()[1], expectedCenter[1]);
    }
    {
      GraveRunnerLevel lvl(1000, 500, 1);
      auto data = BlockData();
      data.block_Type = BlockType::Wall;
      data.blockNumber = 1;
      Vector2D<int> blockSize{64, 50};
      Block *block = new Block(lvl, 15, 44, data, blockSize);

      Vector2D<int> expectedCenter{15 + (blockSize.x / 2), 44 + (blockSize.y / 2)};
      TS_ASSERT_EQUALS(block->getCenter(), expectedCenter);
    }
  }

  void testGetDims() {
    GraveRunnerLevel lvl(1000, 500, 1);
    auto data = BlockData();
    data.block_Type = BlockType::PlainBlock;
    data.blockNumber = 1;
    Vector2D<int> blockSize{128, 100};
    Block *block = new Block(lvl, 0, 0, data, blockSize);
    TS_ASSERT_EQUALS(block->getDims(), blockSize);
  }

  void testGetBlockData() {
    GraveRunnerLevel lvl(1000, 500, 2);
    auto data = BlockData();
    data.block_Type = BlockType::Wall;
    data.blockNumber = 1;
    Vector2D<int> blockSize{64, 50};
    Block *block = new Block(lvl, 15, 44, data, blockSize);

    TS_ASSERT_EQUALS(block->getBlockData(), data);
  }
};
