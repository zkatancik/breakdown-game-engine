#include "editor/EditorManager.hpp"

EditorManager &EditorManager::getInstance() {
  static EditorManager *instance = new EditorManager();
  return *instance;
}

void EditorManager::startUp(int w, int h) {
  // InGame - BG
  background = ResourceManager::getInstance().getTexture(BACKGROUND_IMAGE);
  bg_dest.w = w;
  bg_dest.h = h;
  bg_dest.x = 0;
  bg_dest.y = 0;
  currentLevelNumber = 1;
}

void EditorManager::shutDown() {}

void EditorManager::update() {
  if (editorState_ == EditorState::LevelEditor) currentLevel->update();
}

void EditorManager::render(SDL_Renderer *ren) {
  // In game BG
  SDL_RenderCopy(ren, background, NULL, &bg_dest);
  if (editorState_ == EditorState::LevelEditor) currentLevel->render(ren);
}

EditorManager::EditorState EditorManager::getEditorState() {
  return editorState_;
}

void EditorManager::setEditorState(EditorState es) { editorState_ = es; }

int EditorManager::getLevelVal() { return currentLevelNumber; }

void EditorManager::startEditor() {
  // Load up level from "level" variable.
  score = 0;
  LevelData levelData;
  ResourceManager::getInstance().loadLevel(&levelData, currentLevelNumber);

  rowsOfBlocks = levelData.rowCount;
  blocksPerRow = levelData.colCount;
  currentLevel =
      std::make_shared<GraveRunnerLevel>(blocksPerRow * levelData.blockSize.x,
                                         rowsOfBlocks * levelData.blockSize.y);
  blockSize = levelData.blockSize;

  const int globalXOffset = 220;

  // dynamic y placement of blocks
  int y = 0;
  int count = 1;
  for (int i = 0; i < rowsOfBlocks; i++) {
    int x = globalXOffset;
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
  jack->startUp(globalXOffset + (blockSize.x * levelData.playerStartPosition.x),
                blockSize.y * levelData.playerStartPosition.y, blockSize.x,
                blockSize.y);
  currentLevel->addObject(jack);

  // Place Enemies end points DYNAMICALLY
  for (size_t i = 0; i < levelData.enemyStartPositions.size(); i = i + 2) {
    std::vector<std::pair<float, float>> maleZombie1Path = {
        {globalXOffset + (levelData.enemyStartPositions[i + 1].x * blockSize.x),
         levelData.enemyStartPositions[i + 1].y * blockSize.y}};

    std::shared_ptr<PatrolZombie> maleZombie =
        std::make_shared<PatrolZombie>(*currentLevel);
    maleZombie->startUp(
        globalXOffset + (blockSize.x * levelData.enemyStartPositions[i].x),
        blockSize.y * levelData.enemyStartPositions[i].y, blockSize.x,
        blockSize.y, maleZombie1Path, jack);

    currentLevel->addObject(maleZombie);
  }

  // Place Follower Enemies end points DYNAMICALLY
  for (size_t i = 0; i < levelData.followerEnemyStartPositions.size();
       i = i + 2) {
    std::vector<std::pair<float, float>> maleZombie1Path = {
        {globalXOffset +
             (levelData.followerEnemyStartPositions[i + 1].x * blockSize.x),
         levelData.followerEnemyStartPositions[i + 1].y * blockSize.y}};

    std::shared_ptr<FollowerZombie> maleZombie =
        std::make_shared<FollowerZombie>(*currentLevel);
    maleZombie->startUp(
        globalXOffset +
            (blockSize.x * levelData.followerEnemyStartPositions[i].x),
        blockSize.y * levelData.followerEnemyStartPositions[i].y, blockSize.x,
        blockSize.y, maleZombie1Path, jack);

    enemies.push_back(maleZombie);
    currentLevel->addObject(maleZombie);
  }

  auto level_grid = std::make_shared<GameObject>(
      *currentLevel, globalXOffset, 0, 20 * blockSize.x, 20 * blockSize.y, 44);
  auto gridRenderComponent =
      std::make_shared<GridRenderComponent>(*level_grid, 64, 20, 20);
  level_grid->setRenderComponent(gridRenderComponent);
  currentLevel->setGridRenderComponent(gridRenderComponent);
  currentLevel->addObject(level_grid);

  mLevelData = levelData;
}


void EditorManager::updateCurrentLevel(Vector2D<int> gridPosition,
                                       LevelItem item) {
  // Update the Level
  if (item != LevelItem::NONE) {
    mLevelData.levelGrid[gridPosition.x][gridPosition.y] = item;

    //std::cout << "EM:[After - updateCurrentLevel]:" << std::endl;

    // Update the Level File

    ResourceManager::getInstance().updateLevelFile(mLevelData, gridPosition, item);
  }
}

void EditorManager::clearLevel() {
  // Clear Level.

  rowsOfBlocks = 0;
  blocksPerRow = 0;
  currentLevel = nullptr;

  score = 0;
}
