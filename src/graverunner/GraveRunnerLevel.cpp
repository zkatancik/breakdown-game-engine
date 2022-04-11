#include <box2d/b2_body.h>
#include "graverunner/GraveRunnerLevel.hpp"
#include "graverunner/LevelData.hpp"
#include "graverunner/Tag.hpp"
#include "graverunner/Jack.hpp"
#include "graverunner/FollowerZombie.hpp"
#include "graverunner/PatrolZombie.hpp"
#include "graverunner/GraveRunnerBlock.hpp"
#include "graverunner/KeyBlock.hpp"
#include "graverunner/ExitBlock.hpp"

void GraveRunnerLevel::initialize() {
  finalize();
  GraveRunnerLevelData levelData;
  loadLevel(&levelData, currentLevelNumber);

  int rowsOfBlocks = levelData.rowCount;
  int blocksPerRow = levelData.colCount;
  Vector2D<int> blockSize = levelData.blockSize;

  // Place Level Boundaries (need solid physics component to be considered for
  // collision) Left-most boundary
  auto leftMostBoundary = std::make_shared<GameObject>(
      *this, -1, 0, 1, float(rowsOfBlocks * levelData.blockSize.y),
      GraveRunnerLevelBoundaryTag);
  leftMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *leftMostBoundary, b2BodyType::b2_staticBody, false));
  leftMostBoundary->addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*leftMostBoundary, GraveRunnerBulletTag));
  addObject(leftMostBoundary);
  // Right-most boundary
  auto rightMostBoundary = std::make_shared<GameObject>(
      *this, float(blocksPerRow * levelData.blockSize.x), 0, 1,
      float(rowsOfBlocks * levelData.blockSize.y), GraveRunnerLevelBoundaryTag);
  rightMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *rightMostBoundary, b2BodyType::b2_staticBody, false));
  addObject(rightMostBoundary);
  rightMostBoundary->addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*rightMostBoundary,
                                                 GraveRunnerBulletTag));

  // Place the game objects/environment (blocks, keys, exit)
  int y = 0;
  int count = 1;
  for (int i = 0; i < rowsOfBlocks; i++) {
    int x = 0;
    for (int j = 0; j < blocksPerRow; j++) {
      auto b = levelData.blocks[(i * blocksPerRow) + j];
      if (b.block_Type != GraveRunnerBlockType::NoBlock) {
        std::shared_ptr<GameObject> obj;
        if (b.block_Type == GraveRunnerBlockType::PlainBlock ||
        b.block_Type == GraveRunnerBlockType::Wall) {
          obj = std::make_shared<GraveRunnerBlock>(*this, x, y, b, blockSize);
        } else if (b.block_Type == GraveRunnerBlockType::Key) {
          obj = std::make_shared<KeyBlock>(*this, x, y, blockSize);
        } else if (b.block_Type == GraveRunnerBlockType::Exit) {
          obj = std::make_shared<ExitBlock>(*this, x, y, blockSize);
          initialNumExits++;
        }
        addObject(obj);
      }
      x = x + blockSize.x;
    }
    count++;
    y = y + blockSize.y;
  }

  // Place Jack
  mJack = std::make_shared<Jack>(
      *this, blockSize.x * levelData.playerStartPosition.x,
      blockSize.y * levelData.playerStartPosition.y, blockSize.x, blockSize.y);
  addObject(mJack);

  // Place Enemies end points DYNAMICALLY
  for (size_t i = 0; i < levelData.enemyStartPositions.size(); i = i + 2) {
    std::vector<std::pair<float, float>> maleZombie1Path = {
        {levelData.enemyStartPositions[i + 1].x * blockSize.x,
         levelData.enemyStartPositions[i + 1].y * blockSize.y}};

    std::shared_ptr<PatrolZombie> maleZombie =
        std::make_shared<PatrolZombie>(*this, blockSize.x * levelData.enemyStartPositions[i].x,
                        blockSize.y * levelData.enemyStartPositions[i].y,
                        blockSize.x, blockSize.y, maleZombie1Path, mJack);
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
            blockSize.x, blockSize.y, maleZombie1Path, mJack);
    addObject(maleZombie);
  }

  levelData = mLevelData;
}

bool GraveRunnerLevel::isLevelWon() const {
  int curNumExits = 0;
  bool blocksPresent = false;
  for (const auto& gameobj : getGameObjects()) {
    if (gameobj.get()->tag() == GraveRunnerExitTag) {
      curNumExits++;
    }
    blocksPresent = true;
  }
  return blocksPresent && curNumExits < initialNumExits;
}

bool GraveRunnerLevel::isLevelInProgress() const {
  return mJack.get()->isAlive() && !isLevelWon();
}
