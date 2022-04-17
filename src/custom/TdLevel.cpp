#include "custom/TdLevel.hpp"

#include "base/GameVariableComponent.hpp"
#include "base/GridObject.hpp"
#include "base/PerformHookOnCollideComponent.hpp"
#include "custom/LevelData.hpp"
#include "custom/LevelEditButton.hpp"
#include "custom/Mouse.hpp"
#include "custom/NonHostileEnemy.hpp"
#include "custom/Tag.hpp"
#include "custom/TdBlock.hpp"
#include "custom/RockThrowerTower.hpp"
#include "custom/LevelTimer.hpp"
#include "custom/TdButton.hpp"
#include "base/DelayedSpawnComponent.hpp"

void TdLevel::initialize() {
  // Load level file
  loadLevel(&mLevelData, mLevelNumber);

  int rowsOfBlocks = mLevelData.rowCount;
  int blocksPerRow = mLevelData.colCount;
  Vector2D<int> blockSize = mLevelData.blockSize;
  /********************************************************************************************************************/
  // Create indicators and Game variables
  // Score Indicator
  auto scoreIndicator = createIndicatorObject("Score", 0, 10, 50);
  mScoreIndicator = std::weak_ptr(scoreIndicator);
  // Coins indicator
  auto coinsIndicator = createIndicatorObject("Coins", 20, 10, 80);
  mCoinIndicator = std::weak_ptr(coinsIndicator);
  // Health indicator
  auto healthIndicator = createIndicatorObject("Health", 100, 10, 120);
  mHealthIndicator = std::weak_ptr(healthIndicator);
  // Wave number indicator
  auto waveNumberIndicator = createIndicatorObject("Wave Number", 1, 10, 160);
  mCurrentWaveNumberIndicator = std::weak_ptr(waveNumberIndicator);

  // Level indicator
  auto levelIndicator = createLevelIndicatorObject();
  /********************************************************************************************************************/
  // Add background
  auto background =
      std::make_shared<GameObject>(*this, 0, 0, 1280, 768, TdBGTag);
  auto bg_renderer = std::make_shared<TextureRenderComponent>(*background);
  // All-green background
  bg_renderer->setRenderMode(TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  background->setRenderComponent(bg_renderer);
  bg_renderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/Maps/Backgrounds/TileMap1.png"));
  addObject(background);
  /********************************************************************************************************************/
  // Place the game tiles
  int y = 0;
  int count = 0;
  for (int i = 0; i < rowsOfBlocks; i++) {
    int x = 0;
    for (int j = 0; j < blocksPerRow; j++) {
      auto b = mLevelData.levelGrid[i][j];
      auto placeableBlocks = mLevelData.placableBlockGrid[i][j];

      // Level File.
      if (b.levelItemType != TdLevelItem::NOBLOCK) {
        std::shared_ptr<GameObject> obj;

        if (b.levelItemType == TdLevelItem::PLAINBLOCK) {
          obj = std::make_shared<TdBlock>(*this, x, y, b, blockSize);
        } else if (b.levelItemType == TdLevelItem::PATHBLOCK) {
          obj = std::make_shared<TdBlock>(*this, x, y, b, blockSize);
        } else if (b.levelItemType == TdLevelItem::ROCKTHROWER) {
          obj = std::make_shared<RockThrowerTower>(*this, x, y, blockSize);
        } else {
          std::cerr << "Error- Failed to add level item from row " << i
                    << ", col " << j << " in level file" << std::endl;
        }

        addObject(obj);
      }

      // Tower Map items (Placeablegrid).
      if (placeableBlocks.levelItemType != TdLevelItem::NOBLOCK) {
        std::shared_ptr<GameObject> placeableObj;

        if (placeableBlocks.levelItemType == TdLevelItem::PLACETOWER) {
          placeableObj = std::make_shared<TdBlock>(*this, x, y, placeableBlocks,
                                                   blockSize);
        } else if (placeableBlocks.levelItemType == TdLevelItem::START) {
          placeableObj = std::make_shared<TdBlock>(*this, x, y, placeableBlocks,
                                                   blockSize);
        } else if (placeableBlocks.levelItemType == TdLevelItem::END) {
          placeableObj = std::make_shared<TdBlock>(*this, x, y, placeableBlocks,
                                                   blockSize, TdEndBlockTag);
          placeableObj->addGenericComponent(
              std::make_shared<PerformHookOnCollideComponent>(
                  *placeableObj, TdEnemyTag,
                  [&, healthIndicator =
                          std::weak_ptr<GameObject>(healthIndicator)](
                      Level&, const std::shared_ptr<GameObject>&) {
                    auto healthVarComponent =
                        healthIndicator.lock()
                            ->getGenericComponent<GameVariableComponent<int>>();
                    healthVarComponent->setVariable(
                        healthVarComponent->getVariable() - 20);
                  }));
          placeableObj->addGenericComponent(
              std::make_shared<RemoveOnCollideComponent>(*placeableObj,
                                                         TdEnemyTag));
        } else {
          std::cerr << "Error- Failed to add level item from row " << i
                    << ", col " << j << " in tower map file" << std::endl;
        }

        addObject(placeableObj);
      }

      x = x + blockSize.x;
    }
    count++;
    y = y + blockSize.y;
  }
  /********************************************************************************************************************/
  // Create controls
  createSidebarControls();
  createBottomBarControls();
  /********************************************************************************************************************/
  // Add indicators, grid and Mouse
  addObject(levelIndicator);
  addObject(scoreIndicator);
  addObject(coinsIndicator);
  addObject(healthIndicator);
  addObject(waveNumberIndicator);
  createGrid();
  addObject(std::make_shared<Mouse>(*this));
}

bool TdLevel::isLevelWon() const {
  // TODO- add real win condition
  return false;
}

bool TdLevel::isLevelInProgress() const {
  // TODO- add real inprogress condition
  return true;
}

void TdLevel::createSidebarControls() {
  auto toolbarBackground =
      std::make_shared<GameObject>(*this, w() - xOffset, 0, xOffset,
                                   h(), hash("ToolbarTag"));
  auto backgroundRenderer =
      std::make_shared<TextureRenderComponent>(*toolbarBackground);

  backgroundRenderer->setRenderMode(
      TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  toolbarBackground->setRenderComponent(backgroundRenderer);
  backgroundRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/sidebar.png"));

  addObject(toolbarBackground);

  auto changeToErase = [&] {
    currentlySelected = TdLevelItem::NOBLOCK;
    mGridObject.lock()->setCurrentlySelected("ERASE");
  };

  auto eraseButton = std::make_shared<LevelEditButton>(
      *this, (w() - xOffset) + 109, 35, 74, 74, 5, 5,
      "2DBreakout/Graphics/"
      "erase.png",
      mSoundPath, changeToErase);

  addObject(eraseButton);

  int x = (w() - xOffset) + 20;
  int y = 193;
  int count = 0;

  for (const auto& item : itemVector) {
    auto lambda = [&] {
      currentlySelected = item;
      mGridObject.lock()->setCurrentlySelected(getTdBlockPath(item));
    };
    auto button = std::make_shared<LevelEditButton>(*this, x, y, 74, 74, 5.f,
                                                    5.f, getTdBlockPath(item),
                                                    mSoundPath, lambda, true);
    addObject(button);
    x = x + 89;
    count++;
    if (count == 2) {
      y = y + 79;
      x = (w() - xOffset) + 20;
      count = 0;
    }
  }
}

void TdLevel::createBottomBarControls() {
  auto toolbarBackground = std::make_shared<GameObject>(
      *this, 0, h() - yOffset, w() - xOffset, yOffset,
      hash("ToolbarTag"));
  auto backgroundRenderer =
      std::make_shared<TextureRenderComponent>(*toolbarBackground);

  backgroundRenderer->setRenderMode(
      TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  toolbarBackground->setRenderComponent(backgroundRenderer);
  backgroundRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/bottombar.png"));

  addObject(toolbarBackground);
  auto startWaveLambda = [&] () {
    int currentWaveNumber = mCurrentWaveNumberIndicator.lock()->getGenericComponent<GameVariableComponent<int>>()->getVariable() - 1;
    for (auto enemyInfo : mLevelData.enemyWaves[currentWaveNumber]) {
      for (int i = 0; i < enemyInfo.second; i++) {
        spawnEnemy(enemyInfo.first, i * 3 + 1);
      }
    }
  };
  // Add the start wave button
  auto startWaveButton = std::make_shared<TdButton>(*this, 320, h() - yOffset, 24, 16, "Start Wave!",
                                                    startWaveLambda,
                                                    16);
  addObject(startWaveButton);

}

void TdLevel::createGrid() {
  auto gridCallback = [&, mLevelData = &mLevelData](int i, int j) {
    if (currentlySelected != TdLevelItem::NONE) {
      if (currentlySelected == TdLevelItem::ROCKTHROWER) {
        auto tower = std::make_shared<RockThrowerTower>(*this, i * mLevelData->blockSize.x,
                                                        j * mLevelData->blockSize.y, mLevelData->blockSize);
        for (auto g : getGameObjects()) {
          if (tower->isOverlapping(*g) && g->tag() == TdBlockTag) {
            auto blockGameObject = std::dynamic_pointer_cast<TdBlock>(g).get();
            if (blockGameObject->getBlockData().levelItemType == TdLevelItem::PLACETOWER) {
              Mix_PlayChannel(1, ResourceManager::getInstance().getChunk(mSoundPath),
                              0);
              auto coinIndicatorVariable = mCoinIndicator.lock()->getGenericComponent<GameVariableComponent<int>>();
              if (coinIndicatorVariable->getVariable() >= 10) {
                removeObject(g);
                addObject(tower);
                coinIndicatorVariable->setVariable(coinIndicatorVariable->getVariable() - 10);
              }
            }
          }
        }
      }
      // updateCurrentLevel(mLevelData, Vector2D<int>(i, j), currentlySelected);
    }
  };

  auto gridObject =
      std::make_shared<GridObject>(*this, 0, 0, 20, 12, 64, 64, gridCallback,
                                   getTdBlockPath(currentlySelected));
  mGridObject = std::weak_ptr(gridObject);
  addObject(gridObject);
}

std::shared_ptr<GameObject> TdLevel::createLevelIndicatorObject() {
  auto levelIndicator =
      std::make_shared<GameObject>(*this, 10, 10, 50, 50, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*levelIndicator);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  levelIndicator->setRenderComponent(textRenderer);
  std::string levelMessage = "Level: " + std::to_string(mLevelNumber);
  auto textComponent = std::make_shared<TextComponent>(
      *levelIndicator, levelMessage, 32, "Graverunner/fonts/GADAQUALI.ttf",
      textRenderer);
  levelIndicator->addGenericComponent(textComponent);
  return levelIndicator;
}

std::shared_ptr<GameObject> TdLevel::createIndicatorObject(std::string label,
                                                           int initialVal, int x, int y) {
  auto scoreIndicator =
      std::make_shared<GameObject>(*this, x, y, 50, 50, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*scoreIndicator);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  scoreIndicator->setRenderComponent(textRenderer);
  std::string levelMessage = label + ": " + std::to_string(initialVal);
  // TODO- use a font from TD2D (and/or move one from another game)
  auto textComponent = std::make_shared<TextComponent>(
      *scoreIndicator, levelMessage, 32, "Graverunner/fonts/GADAQUALI.ttf",
      textRenderer);
  scoreIndicator->addGenericComponent(textComponent);
  auto gameVariableComponent =
      std::make_shared<GameVariableComponent<int>>(*scoreIndicator, initialVal);
  scoreIndicator->addGenericComponent(gameVariableComponent);
  std::weak_ptr<GameVariableComponent<int>> gameVariableComponentWeak(
      gameVariableComponent);
  std::weak_ptr<TextComponent> textComponentWeak(textComponent);
  gameVariableComponent->setUpdateCallBack(
      [gameVariableComponentWeak, textComponentWeak, label] {
        textComponentWeak.lock()->SetMText(
            label + ": " +
            std::to_string(gameVariableComponentWeak.lock()->getVariable()));
      });
  return scoreIndicator;
}

std::string TdLevel::getTdBlockPath(TdLevelItem item) {
  switch (item) {
    case TdLevelItem::NONE:
      return "TD2D/Sprites/Tiles/Empty.png";
    case TdLevelItem::NOBLOCK:
      return "";
    case TdLevelItem::PLACETOWER:
      return "TD2D/Sprites/Towers/BuildingPlace.png";
    case TdLevelItem::ROCKTHROWER:
      return "TD2D/Sprites/Towers/cpix_towers/3.png";
    default:
      std::cerr << "Failed to get Graverunner block path for item "
                << static_cast<int>(item) << std::endl;
      return "";
  }
}
void TdLevel::spawnEnemy(TdLevelItem enemyType, int delay) {
  // Function to increase coin and score upon death
  auto increaseScoreAndCoinsIndicatorLambda = [&]() {
    auto scoreVarComponent =
        mScoreIndicator.lock()
        ->getGenericComponent<GameVariableComponent<int>>();
    auto coinsVarComponent =
        mCoinIndicator.lock()
        ->getGenericComponent<GameVariableComponent<int>>();
    scoreVarComponent->setVariable(scoreVarComponent->getVariable() + 10);
    coinsVarComponent->setVariable(coinsVarComponent->getVariable() + 5);
  };
  // Actual constructor
  std::shared_ptr<NonHostileEnemy> enemy = std::make_shared<NonHostileEnemy>(
      *this, mLevelData.blockSize.x * mLevelData.startPosition.x,
      mLevelData.blockSize.y * mLevelData.startPosition.y, mLevelData.blockSize.x, mLevelData.blockSize.y,
      "4/4_enemies_1_run_", enemyType, mLevelData.endPosition,
      mLevelData.levelGrid, increaseScoreAndCoinsIndicatorLambda);
  // Decrease score and lives when reaching the end of the line
  auto decreaseScoreAndLivesIndicatorLambda = [&](Level& level, std::shared_ptr<GameObject> gameObject) {
    auto scoreVarComponent =
        mScoreIndicator.lock()
        ->getGenericComponent<GameVariableComponent<int>>();
    auto healthVarComponent =
        mHealthIndicator.lock()
        ->getGenericComponent<GameVariableComponent<int>>();
    scoreVarComponent->setVariable(scoreVarComponent->getVariable() - 5);
    healthVarComponent->setVariable(healthVarComponent->getVariable() - 1);
  };
  enemy->addGenericComponent(std::make_shared<PerformHookOnCollideComponent>(
      *enemy, TdEndBlockTag, decreaseScoreAndLivesIndicatorLambda));
  enemy->addGenericComponent(std::make_shared<DelayedSpawnComponent>(*enemy, delay));
  addObject(enemy);
}
