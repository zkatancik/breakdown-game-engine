#include "graverunner/GameManager.hpp"

GameManager &GameManager::getInstance() {
  static GameManager *instance = new GameManager();
  return *instance;
}

void GameManager::startUp(int w, int h) {
  // InGame - BG
  background = ResourceManager::getInstance().getTexture(BACKGROUND_IMAGE);
  bg_dest.w = w;
  bg_dest.h = h;
  bg_dest.x = 0;
  bg_dest.y = 0;
  currentLevelNumber = 1;
  // Music Volume adjustment
  Mix_VolumeMusic(MIX_MAX_VOLUME / 6);
  Mix_PlayMusic(
      ResourceManager::getInstance().getMusic("ClassicsIV-Spooky.wav"), -1);
  Mix_Volume(0, MIX_MAX_VOLUME);
  Mix_Volume(1, MIX_MAX_VOLUME / 6);
}

void GameManager::shutDown() {
}

void GameManager::update() {
  if (isGameStarted()) {
    currentLevel->update();
    score = int(jack->GetNumCollectedKeys());
    if (isGameEnd()) {
      gameState_ = GameState::GameEnd;
    }

    if (InputManager::getInstance().isKeyDown(SDLK_x)) {
      updateLevel();
      gameState_ = GameState::GameEnd;
    }
  }
}

void GameManager::render(SDL_Renderer *ren) {
  if (isGameStarted()) {
    // In game BG
    SDL_RenderCopy(ren, background, NULL, &bg_dest);

    currentLevel->render(ren);
  }
}

GameManager::GameState GameManager::getGameState() { return gameState_; }

void GameManager::setGameState(GameState gs) { gameState_ = gs; }

bool GameManager::isGameStarted() { return (gameState_ == GameState::InGame); }

bool GameManager::isGameEnd() { return !jack->isAlive() || isGameWon(); }

int GameManager::getScoreVal() { return score; }

int GameManager::getLevelVal() { return currentLevelNumber; }

void GameManager::startGame() {
  // Load up level from "level" variable.
  score = 0;
  LevelData levelData;
  ResourceManager::getInstance().loadLevel(&levelData, currentLevelNumber);

  rowsOfBlocks = levelData.rowCount;
  blocksPerRow = levelData.colCount;
  currentLevel = std::make_shared<GraveRunnerLevel>(blocksPerRow * levelData.blockSize.x,
                                                    rowsOfBlocks * levelData.blockSize.y);
  blockSize = levelData.blockSize;

  // Place Level Boundaries (need solid physics component to be considered for
  // collision) Left-most boundary
  auto leftMostBoundary = std::make_shared<GameObject>(*currentLevel,
      -1, 0, 1, float(rowsOfBlocks * levelData.blockSize.y), LevelBoundaryTag);
  leftMostBoundary->setPhysicsComponent(
      std::make_shared<PhysicsComponent>(*leftMostBoundary, PhysicsComponent::Type::STATIC_SOLID));
  leftMostBoundary->addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*leftMostBoundary, BulletTag));
  currentLevel->addObject(leftMostBoundary);
  // Right-most boundary
  auto rightMostBoundary = std::make_shared<GameObject>(*currentLevel,
      float(blocksPerRow * levelData.blockSize.x), 0, 1,
      float(rowsOfBlocks * levelData.blockSize.y), LevelBoundaryTag);
  rightMostBoundary->setPhysicsComponent(
      std::make_shared<PhysicsComponent>(*rightMostBoundary, PhysicsComponent::Type::STATIC_SOLID));
  currentLevel->addObject(rightMostBoundary);
  rightMostBoundary->addGenericComponent(std::make_shared<RemoveOnCollideComponent>(*rightMostBoundary, BulletTag));

  // dynamic y placement of blocks
  int y = 0;
  int count = 1;
  for (int i = 0; i < rowsOfBlocks; i++) {
    int x = 0;
    for (int j = 0; j < blocksPerRow; j++) {
      auto b = levelData.blocks[(i * blocksPerRow) + j];
      if (b.block_Type != BlockType::NoBlock) {
        auto block = std::make_shared<Block>(*currentLevel);
        if (b.block_Type == BlockType::PlainBlock) {
          block->startUp(x, y, b, 1, blockSize);
        } else if (b.block_Type == BlockType::HardBlock) {
          block->startUp(x, y, b, 3, blockSize);
        } else if (b.block_Type == BlockType::Wall) {
          block->startUp(x, y, b, 0, blockSize);
        } else if (b.block_Type == BlockType::Key) {
          block->startUp(x, y, b, 0, blockSize);
        } else if (b.block_Type == BlockType::Exit) {
          exitBlock = block;
          block->startUp(x, y, b, 0, blockSize);
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

    std::shared_ptr<PatrolZombie> maleZombie = std::make_shared<PatrolZombie>(*currentLevel);
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

    std::shared_ptr<FollowerZombie> maleZombie = std::make_shared<FollowerZombie>(*currentLevel);
    maleZombie->startUp(blockSize.x * levelData.followerEnemyStartPositions[i].x,
                        blockSize.y * levelData.followerEnemyStartPositions[i].y,
                        blockSize.x,
                        blockSize.y,
                        maleZombie1Path,
                        jack);
    currentLevel->addObject(maleZombie);
  }

  levelData = mLevelData;
}

void GameManager::clearLevel() {
  // Clear Level.

  rowsOfBlocks = 0;
  blocksPerRow = 0;
  currentLevel = nullptr;

  score = 0;
}

bool GameManager::isGameWon() {
  return !currentLevel->FindObject(exitBlock);
}

void GameManager::updateLevel() {
  if (currentLevelNumber < MAX_LEVEL) {
    currentLevelNumber++;
  } else {
    // Reset levels after all are passed.
    currentLevelNumber = 1;
  }
}
