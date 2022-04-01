#include <cxxtest/TestSuite.h>

#include "graverunner/Block.hpp"
#include "graverunner/LevelData.hpp"
#include "graverunner/GraveRunnerLevel.hpp"

class BlockTestSuite : public CxxTest::TestSuite {
 public:
  const float EPSILON = 0.001f;

  // --------------------- BLOCK TESTS -----------------------------------

  void testStartUp() {
    GraveRunnerLevel lvl(1000, 500);
    Block *block = new Block(lvl);
    auto data = BlockData();
    data.block_Type = BlockType::PlainBlock;
    data.blockNumber = 1;
    Vector2D<int> blockSize{128, 128};
    block->startUp(0, 0, data, 1, blockSize);
  }

  void testShutDown() {}

  void testUpdate() {}

  void testRender() {}

  void testGetCenter() {
    GraveRunnerLevel lvl(1000, 500);
    Block *block = new Block(lvl);
    auto data = BlockData();
    data.block_Type = BlockType::PlainBlock;
    data.blockNumber = 1;
    Vector2D<int> blockSize{128, 128};
    block->startUp(0, 0, data, 1, blockSize);
    Vector2D<int> u{};
    u[0] = 64;
    u[1] = 64;
    TS_ASSERT_EQUALS(block->getCenter()[0], u[0]);
    TS_ASSERT_EQUALS(block->getCenter()[1], u[1]);
  }

  void testGetDims() {
    GraveRunnerLevel lvl(1000, 500);
    Block *block = new Block(lvl);
    auto data = BlockData();
    data.block_Type = BlockType::PlainBlock;
    data.blockNumber = 1;
    Vector2D<int> blockSize{128, 128};
    block->startUp(100, 100, data, 1, blockSize);
    Vector2D<int> u{};
    u[0] = 128;
    u[1] = 128;
    TS_ASSERT_EQUALS(block->getDims()[0], u[0]);
    TS_ASSERT_EQUALS(block->getDims()[1], u[1]);
  }
};
