#include <box2d/b2_body.h>
#include "graverunner/GraveRunnerLevel.hpp"
#include "graverunner/LevelData.hpp"
#include "graverunner/Tag.hpp"
#include "graverunner/Jack.hpp"
#include "graverunner/FollowerZombie.hpp"
#include "graverunner/PatrolZombie.hpp"
#include "graverunner/Block.hpp"
#include "graverunner/KeyBlock.hpp"
#include "graverunner/ExitBlock.hpp"

void GraveRunnerLevel::initialize() {
  finalize();
  LevelData levelData;
  loadLevel(&levelData, currentLevelNumber);

  int rowsOfBlocks = levelData.rowCount;
  int blocksPerRow = levelData.colCount;
  Vector2D<int> blockSize = levelData.blockSize;

  // Place Level Boundaries (need solid physics component to be considered for
  // collision) Left-most boundary
  auto leftMostBoundary = std::make_shared<GameObject>(
      *this, -1, 0, 1, float(rowsOfBlocks * levelData.blockSize.y),
      LevelBoundaryTag);
  leftMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *leftMostBoundary, b2BodyType::b2_staticBody, false));
  leftMostBoundary->addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*leftMostBoundary, BulletTag));
  addObject(leftMostBoundary);
  // Right-most boundary
  auto rightMostBoundary = std::make_shared<GameObject>(
      *this, float(blocksPerRow * levelData.blockSize.x), 0, 1,
      float(rowsOfBlocks * levelData.blockSize.y), LevelBoundaryTag);
  rightMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *rightMostBoundary, b2BodyType::b2_staticBody, false));
  addObject(rightMostBoundary);
  rightMostBoundary->addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*rightMostBoundary,
                                                 BulletTag));

  // Place the game objects/environment (blocks, keys, exit)
  int y = 0;
  int count = 1;
  for (int i = 0; i < rowsOfBlocks; i++) {
    int x = 0;
    for (int j = 0; j < blocksPerRow; j++) {
      auto b = levelData.blocks[(i * blocksPerRow) + j];
      if (b.block_Type != BlockType::NoBlock) {
        std::shared_ptr<GameObject> obj;
        if (b.block_Type == BlockType::PlainBlock ||
            b.block_Type == BlockType::Wall) {
          obj = std::make_shared<Block>(*this, x, y, b, blockSize);
        } else if (b.block_Type == BlockType::Key) {
          obj = std::make_shared<KeyBlock>(*this, x, y, blockSize);
        } else if (b.block_Type == BlockType::Exit) {
          obj = std::make_shared<ExitBlock>(*this, x, y, blockSize);
        }
        addObject(obj);
      }
      x = x + blockSize.x;
    }
    count++;
    y = y + blockSize.y;
  }

  // Place Jack
  std::shared_ptr<Jack> jack = std::make_shared<Jack>(
      *this, blockSize.x * levelData.playerStartPosition.x,
      blockSize.y * levelData.playerStartPosition.y, blockSize.x, blockSize.y);
  addObject(jack);

  // Place Enemies end points DYNAMICALLY
  for (size_t i = 0; i < levelData.enemyStartPositions.size(); i = i + 2) {
    std::vector<std::pair<float, float>> maleZombie1Path = {
        {levelData.enemyStartPositions[i + 1].x * blockSize.x,
         levelData.enemyStartPositions[i + 1].y * blockSize.y}};

    std::shared_ptr<PatrolZombie> maleZombie =
        std::make_shared<PatrolZombie>(*this, blockSize.x * levelData.enemyStartPositions[i].x,
                        blockSize.y * levelData.enemyStartPositions[i].y,
                        blockSize.x, blockSize.y, maleZombie1Path, jack);
    addObject(maleZombie);
  }

  // Place Follower Enemies end points DYNAMICALLY
  for (size_t i = 0; i < levelData.followerEnemyStartPositions.size();
       i = i + 2) {
    std::vector<std::pair<float, float>> maleZombie1Path = {
        {levelData.followerEnemyStartPositions[i + 1].x * blockSize.x,
         levelData.followerEnemyStartPositions[i + 1].y * blockSize.y}};

    std::shared_ptr<FollowerZombie> maleZombie =
        std::make_shared<FollowerZombie>(
            *this,
            blockSize.x * levelData.followerEnemyStartPositions[i].x,
            blockSize.y * levelData.followerEnemyStartPositions[i].y,
            blockSize.x, blockSize.y, maleZombie1Path, jack);
    addObject(maleZombie);
  }

  levelData = mLevelData;
}
