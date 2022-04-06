#include "graverunner/GraveRunnerLevel.hpp"
#include "graverunner/LevelData.hpp"
#include "graverunner/Tag.hpp"
#include "graverunner/Jack.hpp"

void GraveRunnerLevel::initialize() {
  finalize();
  LevelData levelData;
  loadLevel(&levelData, currentLevelNumber);

  rowsOfBlocks = levelData.rowCount;
  blocksPerRow = levelData.colCount;
  currentLevel =
      std::make_shared<GraveRunnerLevel>(blocksPerRow * levelData.blockSize.x,
                                         rowsOfBlocks * levelData.blockSize.y);
  blockSize = levelData.blockSize;

  // Place Level Boundaries (need solid physics component to be considered for
  // collision) Left-most boundary
  auto leftMostBoundary = std::make_shared<GameObject>(
      *currentLevel, -1, 0, 1, float(rowsOfBlocks * levelData.blockSize.y),
      LevelBoundaryTag);
  leftMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *leftMostBoundary, PhysicsComponent::Type::STATIC_SOLID));
  leftMostBoundary->addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*leftMostBoundary, BulletTag));
  currentLevel->addObject(leftMostBoundary);
  // Right-most boundary
  auto rightMostBoundary = std::make_shared<GameObject>(
      *currentLevel, float(blocksPerRow * levelData.blockSize.x), 0, 1,
      float(rowsOfBlocks * levelData.blockSize.y), LevelBoundaryTag);
  rightMostBoundary->setPhysicsComponent(std::make_shared<PhysicsComponent>(
      *rightMostBoundary, PhysicsComponent::Type::STATIC_SOLID));
  currentLevel->addObject(rightMostBoundary);
  rightMostBoundary->addGenericComponent(
      std::make_shared<RemoveOnCollideComponent>(*rightMostBoundary,
                                                 BulletTag));

  // dynamic y placement of blocks
  int y = 0;
  int count = 1;
  for (int i = 0; i < rowsOfBlocks; i++) {
    int x = 0;
    for (int j = 0; j < blocksPerRow; j++) {
      auto b = levelData.blocks[(i * blocksPerRow) + j];
      if (b.block_Type != BlockType::NoBlock) {
        std::shared_ptr<Block> block;
        if (b.block_Type == BlockType::PlainBlock) {
          block = std::make_shared<Block>(*currentLevel, x, y, b, 1, blockSize);
        } else if (b.block_Type == BlockType::HardBlock) {
          block = std::make_shared<Block>(*currentLevel, x, y, b, 3, blockSize);
        } else if (b.block_Type == BlockType::Wall) {
          block = std::make_shared<Block>(*currentLevel, x, y, b, 0, blockSize);
        } else if (b.block_Type == BlockType::Key) {
          block = std::make_shared<Block>(*currentLevel, x, y, b, 0, blockSize);
        } else if (b.block_Type == BlockType::Exit) {
          block = std::make_shared<Block>(*currentLevel, x, y, b, 0, blockSize);
          exitBlock = block;
        }
        currentLevel->addObject(block);
      }
      x = x + blockSize.x;
    }
    count++;
    y = y + blockSize.y;
  }

  // Place Jack
  jack = std::make_shared<Jack>(*currentLevel);
  jack->startUp(blockSize.x * levelData.playerStartPosition.x,
                blockSize.y * levelData.playerStartPosition.y, blockSize.x,
                blockSize.y);
  currentLevel->addObject(jack);

  // Place Enemies end points DYNAMICALLY
  for (size_t i = 0; i < levelData.enemyStartPositions.size(); i = i + 2) {
    std::vector<std::pair<float, float>> maleZombie1Path = {
        {levelData.enemyStartPositions[i + 1].x * blockSize.x,
         levelData.enemyStartPositions[i + 1].y * blockSize.y}};

    std::shared_ptr<PatrolZombie> maleZombie =
        std::make_shared<PatrolZombie>(*currentLevel);
    maleZombie->startUp(blockSize.x * levelData.enemyStartPositions[i].x,
                        blockSize.y * levelData.enemyStartPositions[i].y,
                        blockSize.x, blockSize.y, maleZombie1Path, jack);

    currentLevel->addObject(maleZombie);
  }

  // Place Follower Enemies end points DYNAMICALLY
  for (size_t i = 0; i < levelData.followerEnemyStartPositions.size();
       i = i + 2) {
    std::vector<std::pair<float, float>> maleZombie1Path = {
        {levelData.followerEnemyStartPositions[i + 1].x * blockSize.x,
         levelData.followerEnemyStartPositions[i + 1].y * blockSize.y}};

    std::shared_ptr<FollowerZombie> maleZombie =
        std::make_shared<FollowerZombie>(
            *currentLevel,
            blockSize.x * levelData.followerEnemyStartPositions[i].x,
            blockSize.y * levelData.followerEnemyStartPositions[i].y,
            blockSize.x, blockSize.y, maleZombie1Path, jack);
    currentLevel->addObject(maleZombie);
  }

  levelData = mLevelData;
}
