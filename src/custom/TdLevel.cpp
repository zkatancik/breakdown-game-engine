#include "custom/TdLevel.hpp"

#include "base/TextMessageObject.hpp"
#include "custom/AntiTankMine.hpp"

void TdLevel::initialize() {
  // Load level file
  mNumEnemiesLeft = 0;
  loadLevel(&mLevelData, mLevelNumber);

  int rowsOfBlocks = mLevelData.rowCount;
  int blocksPerRow = mLevelData.colCount;
  Vector2D<int> blockSize = mLevelData.blockSize;
  /********************************************************************************************************************/
  // Create indicators and Game variables

  // Wave number indicator
  auto waveNumberIndicator = createIndicatorObject("Wave Number", 1, 1300, 15);
  mCurrentWaveNumberIndicator = std::weak_ptr(waveNumberIndicator);
  // Score Indicator
  auto scoreIndicator = createIndicatorObject("Score", 0, 1300, 50);
  mScoreIndicator = std::weak_ptr(scoreIndicator);
  // Health indicator
  auto healthIndicator = createIndicatorObject("Health", 200, 1300, 100);
  mHealthIndicator = std::weak_ptr(healthIndicator);
  // Coins indicator
  auto coinsIndicator = createIndicatorObject("Coins", 40, 1300, 135);
  mCoinIndicator = std::weak_ptr(coinsIndicator);

  // Level indicator
  auto levelIndicator = createLevelIndicatorObject();
  /********************************************************************************************************************/
  // Create icons for health and coins indicators

  // Health Icon
  auto healthIcon =
      std::make_shared<GameObject>(*this, 1300, 95, 50, 50, BaseTextTag);
  auto hIconRenderer = std::make_shared<TextureRenderComponent>(*healthIcon);

  hIconRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  healthIcon->setRenderComponent(hIconRenderer);
  hIconRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/life_0.png"));
  // Coins Icon
  auto coinsIcon =
      std::make_shared<GameObject>(*this, 1300, 130, 50, 50, BaseTextTag);
  auto cIconRenderer = std::make_shared<TextureRenderComponent>(*coinsIcon);

  cIconRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  coinsIcon->setRenderComponent(cIconRenderer);
  cIconRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/coin_0.png"));

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
        } else if (b.levelItemType == TdLevelItem::PATHBLOCK0 ||
                   b.levelItemType == TdLevelItem::PATHBLOCK1 ||
                   b.levelItemType == TdLevelItem::PATHBLOCK2 ||
                   b.levelItemType == TdLevelItem::PATHBLOCK3 ||
                   b.levelItemType == TdLevelItem::PATHBLOCK4 ||
                   b.levelItemType == TdLevelItem::PATHBLOCK5 ||
                   b.levelItemType == TdLevelItem::PATHBLOCK6 ||
                   b.levelItemType == TdLevelItem::PATHBLOCK7 ||
                   b.levelItemType == TdLevelItem::PATHBLOCK8 ||
                   b.levelItemType == TdLevelItem::PATHBLOCK9 ||
                   b.levelItemType == TdLevelItem::PATHBLOCKA) {
          obj = std::make_shared<TdBlock>(*this, x, y, b, blockSize);
        } else if (b.levelItemType == TdLevelItem::ROCKTHROWER) {
          obj = std::make_shared<RockThrowerTower>(*this, x, y, blockSize);
        } else if (b.levelItemType == TdLevelItem::MAGICTOWER) {
          obj = std::make_shared<MagicTower>(*this, x, y, blockSize);
        } else if (b.levelItemType == TdLevelItem::ARROWTOWER) {
          obj = std::make_shared<ArrowTower>(*this, x, y, blockSize);
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
  // Place Env
  for (int i = 0; i < mLevelData.levelEnvItems.size(); i++) {
    std::shared_ptr<GameObject> envObj;
    auto envItemInfo = mLevelData.levelEnvItems[i];
    auto envItemPos = mLevelData.levelEnvItemPositions[i];
    envObj = std::make_shared<TdBlock>(*this, envItemPos.x, envItemPos.y,
                                       envItemInfo, blockSize);
    addObject(envObj);
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
}

bool TdLevel::isLevelWon() const {
  auto waveNumberVariable =
      mCurrentWaveNumberIndicator.lock()
          ->getGenericComponent<GameVariableComponent<int>>();
  auto healthVariable = mHealthIndicator.lock()
                            ->getGenericComponent<GameVariableComponent<int>>();
  return ((size_t)(waveNumberVariable->getVariable() - 1) ==
              mLevelData.enemyWaves.size() &&
          healthVariable->getVariable() > 0);
}

bool TdLevel::isLevelInProgress() const {
  auto waveNumberVariable =
      mCurrentWaveNumberIndicator.lock()
          ->getGenericComponent<GameVariableComponent<int>>();
  auto healthVariable = mHealthIndicator.lock()
                            ->getGenericComponent<GameVariableComponent<int>>();
  return ((size_t)(waveNumberVariable->getVariable() - 1) <
              mLevelData.enemyWaves.size() &&
          healthVariable->getVariable() > 0);
}

void TdLevel::createSidebarControls() {
  auto toolbarBackground = std::make_shared<GameObject>(
      *this, w() - sideBarXOffset, 0, sideBarXOffset, h(), TdToolbarTag);
  auto backgroundRenderer =
      std::make_shared<TextureRenderComponent>(*toolbarBackground);

  backgroundRenderer->setRenderMode(
      TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  toolbarBackground->setRenderComponent(backgroundRenderer);
  backgroundRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/sidebar.png"));

  addObject(toolbarBackground);

  int x = (w() - sideBarXOffset) + 20;
  int y = 193;
  int count = 0;

  for (const auto& item : itemVector) {
    auto lambda = [&] {
      currentlySelected = item;
      mGridObject.lock()->setCurrentlySelected(getTdBlockPath(item));
    };
    auto button = std::make_shared<CustomLevelEditButton>(
        *this, x, y, 74, 74, 5.f, 5.f, getTdBlockPath(item), mSoundPath, lambda,
        true);
    addObject(button);
    x = x + 89;
    count++;
    if (count == 2) {
      y = y + 79;
      x = (w() - sideBarXOffset) + 20;
      count = 0;
    }
  }
}

void TdLevel::createBottomBarControls() {
  auto toolbarBackground = std::make_shared<GameObject>(
      *this, 0, h() - sideBarYOffset, w() - sideBarXOffset, sideBarYOffset,
      TdToolbarTag);
  auto backgroundRenderer =
      std::make_shared<TextureRenderComponent>(*toolbarBackground);

  backgroundRenderer->setRenderMode(
      TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  toolbarBackground->setRenderComponent(backgroundRenderer);
  backgroundRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/bottombar.png"));

  addObject(toolbarBackground);

  auto startWaveLambda = [&]() {
    if (mNumEnemiesLeft == 0) {
      int currentWaveNumber =
          mCurrentWaveNumberIndicator.lock()
              ->getGenericComponent<GameVariableComponent<int>>()
              ->getVariable() -
          1;
      Mix_PlayChannel(1,
                      ResourceManager::getInstance().getChunk(
                          "TD2D/Audio/Common/WaveStart1.mp3"),
                      0);
      for (auto enemyInfo : mLevelData.enemyWaves[currentWaveNumber]) {
        for (int i = 0; i < enemyInfo.second; i++) {
          spawnEnemy(enemyInfo.first, i * 2 + std::rand() % 5, i);
        }
      }
      mStartWaveButton.lock()->setIsVisibleOnScreen(false);
    }
  };

  // Add the start wave button
  auto startWaveButton =
      std::make_shared<TdButton>(*this, 320, h() - sideBarYOffset, 24, 16,
                                 "Start Wave!", startWaveLambda, 16);
  mStartWaveButton = std::weak_ptr(startWaveButton);
  mStartWaveButton.lock()->setTag(TdStartWaveButtonTag);
  addObject(startWaveButton);

  // Create Tower Details Panel
  float nextXOffset = 0;
  auto towerDesc = std::make_shared<TextMessageObject>(
      *this, "Tower **", 320 + nextXOffset, h() - sideBarYOffset + 15,
      "TD2D/Fonts/ds-coptic.ttf", 16);
  auto towerSellText = std::make_shared<TextMessageObject>(
      *this, "Sell value: 10", 320 + nextXOffset,
      h() - (sideBarYOffset / 2.0) + 15, "TD2D/Fonts/ds-coptic.ttf", 16);

  nextXOffset += 200;
  auto towerFireModeText = std::make_shared<TextMessageObject>(
      *this, "Fire Mode:", 320 + nextXOffset, h() - sideBarYOffset + 15,
      "TD2D/Fonts/ds-coptic.ttf", 16);
  mTowerDescText = std::weak_ptr(towerDesc);
  mTowerSellText = std::weak_ptr(towerSellText);
  mTowerFMText = std::weak_ptr(towerFireModeText);
  addObject(towerDesc);
  addObject(towerSellText);
  addObject(towerFireModeText);

  nextXOffset += 400;
  auto fmClosestButton =
      std::make_shared<TdButton>(*this, 320 + nextXOffset, h() - sideBarYOffset,
                                 24, 16, "Closest", startWaveLambda, 16);
  mFMClosestButton = std::weak_ptr(fmClosestButton);
  addObject(fmClosestButton);

  nextXOffset += 400;
  auto fmFirstButton =
      std::make_shared<TdButton>(*this, 320 + nextXOffset, h() - sideBarYOffset,
                                 24, 16, "First", startWaveLambda, 16);
  mFMFirstButton = std::weak_ptr(fmFirstButton);
  addObject(fmFirstButton);

  nextXOffset += 300;
  auto fmLastButton =
      std::make_shared<TdButton>(*this, 320 + nextXOffset, h() - sideBarYOffset,
                                 24, 16, "Last", startWaveLambda, 16);
  mFMLastButton = std::weak_ptr(fmLastButton);
  addObject(fmLastButton);

  nextXOffset += 375;
  auto fmStrongestButton =
      std::make_shared<TdButton>(*this, 320 + nextXOffset, h() - sideBarYOffset,
                                 24, 16, "Strongest", startWaveLambda, 16);
  mFMStrongestButton = std::weak_ptr(fmStrongestButton);
  addObject(fmStrongestButton);
  hideTowerDetails();
}

void TdLevel::createGrid() {
  auto gridObject =
      std::make_shared<GridObject>(*this, 0, 0, 20, 12, 64, 64,
                                   getTdBlockPath(currentlySelected));
  mGridObject = std::weak_ptr(gridObject);

  auto gridCallback = [&, mLevelData = &mLevelData](int i, int j, int x,
                                                    int y) {
    if (currentlySelected == TdLevelItem::ROCKTHROWER) {
      auto tower = std::make_shared<RockThrowerTower>(
          *this, i * mLevelData->blockSize.x, j * mLevelData->blockSize.y,
          mLevelData->blockSize);
      for (auto g : getGameObjects()) {
        if (tower->isOverlapping(*g) && g->tag() == TdBlockTag) {
          auto blockGameObject = std::dynamic_pointer_cast<TdBlock>(g).get();
          if (blockGameObject->getBlockData().levelItemType ==
              TdLevelItem::PLACETOWER) {
            Mix_PlayChannel(
                1, ResourceManager::getInstance().getChunk(mSoundPath), 0);
            auto coinIndicatorVariable =
                mCoinIndicator.lock()
                    ->getGenericComponent<GameVariableComponent<int>>();
            if (coinIndicatorVariable->getVariable() >= 10) {
              removeObject(g);
              addObject(tower);
              coinIndicatorVariable->setVariable(
                  coinIndicatorVariable->getVariable() - 10);
              Mix_PlayChannel(1,
                              ResourceManager::getInstance().getChunk(
                                  "TD2D/Audio/Common/Construct1.mp3"),
                              0);
              currentlySelected = TdLevelItem::NONE;
              mGridObject.lock()->setCurrentlySelected("TD2D/Sprites/Tiles/Empty.png");
            }
          }
        }
      }
    } else if (currentlySelected == TdLevelItem::MAGICTOWER) {
      auto tower = std::make_shared<MagicTower>(
          *this, i * mLevelData->blockSize.x, j * mLevelData->blockSize.y,
          mLevelData->blockSize);
      for (auto g : getGameObjects()) {
        if (tower->isOverlapping(*g) && g->tag() == TdBlockTag) {
          auto blockGameObject = std::dynamic_pointer_cast<TdBlock>(g).get();
          if (blockGameObject->getBlockData().levelItemType ==
              TdLevelItem::PLACETOWER) {
            Mix_PlayChannel(
                1, ResourceManager::getInstance().getChunk(mSoundPath), 0);
            auto coinIndicatorVariable =
                mCoinIndicator.lock()
                    ->getGenericComponent<GameVariableComponent<int>>();
            if (coinIndicatorVariable->getVariable() >= 20) {
              removeObject(g);
              addObject(tower);
              coinIndicatorVariable->setVariable(
                  coinIndicatorVariable->getVariable() - 20);
              Mix_PlayChannel(1,
                              ResourceManager::getInstance().getChunk(
                                  "TD2D/Audio/Common/Construct1.mp3"),
                              0);
              currentlySelected = TdLevelItem::NONE;
              mGridObject.lock()->setCurrentlySelected("TD2D/Sprites/Tiles/Empty.png");
            }
          }
        }
      }
    } else if (currentlySelected == TdLevelItem::ARROWTOWER) {
      auto tower = std::make_shared<ArrowTower>(
          *this, i * mLevelData->blockSize.x, j * mLevelData->blockSize.y,
          mLevelData->blockSize);
      for (auto g : getGameObjects()) {
        if (tower->isOverlapping(*g) && g->tag() == TdBlockTag) {
          auto blockGameObject = std::dynamic_pointer_cast<TdBlock>(g).get();
          if (blockGameObject->getBlockData().levelItemType ==
              TdLevelItem::PLACETOWER) {
            Mix_PlayChannel(
                1, ResourceManager::getInstance().getChunk(mSoundPath), 0);
            auto coinIndicatorVariable =
                mCoinIndicator.lock()
                    ->getGenericComponent<GameVariableComponent<int>>();
            if (coinIndicatorVariable->getVariable() >= 15) {
              removeObject(g);
              addObject(tower);
              coinIndicatorVariable->setVariable(
                  coinIndicatorVariable->getVariable() - 15);
              Mix_PlayChannel(1,
                              ResourceManager::getInstance().getChunk(
                                  "TD2D/Audio/Common/Construct1.mp3"),
                              0);
              currentlySelected = TdLevelItem::NONE;
              mGridObject.lock()->setCurrentlySelected("TD2D/Sprites/Tiles/Empty.png");
            }
          }
        }
      }
    } else if (currentlySelected == TdLevelItem::ANTITANKMINE) {
      auto mine = std::make_shared<AntiTankMine>(
          *this, i * mLevelData->blockSize.x, j * mLevelData->blockSize.y,
          mLevelData->blockSize);
      std::vector<std::shared_ptr<GameObject>> overLaps;
      bool performPlacement = true;
      for (auto g : getGameObjects()) {
        if (mine->isOverlapping(*g)) {
          overLaps.push_back(g);
          if (g->tag() == TdAntiTankTowerTag) performPlacement = false;
        }
      }
      for (auto g : overLaps) {
        if (performPlacement && mine->isOverlapping(*g) &&
            g->tag() == TdBlockTag) {
          auto blockGameObject = std::dynamic_pointer_cast<TdBlock>(g).get();
          if (blockGameObject &&
              blockGameObject->getBlockData().levelItemType !=
                  TdLevelItem::PLACETOWER &&
              blockGameObject->getBlockData().levelItemType !=
                  TdLevelItem::PLAINBLOCK &&
              blockGameObject->getBlockData().levelItemType !=
                  TdLevelItem::START &&
              blockGameObject->getBlockData().levelItemType !=
                  TdLevelItem::END) {
            Mix_PlayChannel(
                1, ResourceManager::getInstance().getChunk(mSoundPath), 0);
            auto coinIndicatorVariable =
                mCoinIndicator.lock()
                    ->getGenericComponent<GameVariableComponent<int>>();
            if (coinIndicatorVariable->getVariable() >= 20) {
              addObject(mine);
              coinIndicatorVariable->setVariable(
                  coinIndicatorVariable->getVariable() - 20);
              Mix_PlayChannel(1,
                              ResourceManager::getInstance().getChunk(
                                  "TD2D/Audio/Common/Construct1.mp3"),
                              0);
              currentlySelected = TdLevelItem::NONE;
              mGridObject.lock()->setCurrentlySelected("TD2D/Sprites/Tiles/Empty.png");
            }
          }
        }
      }
    } else if (currentlySelected == TdLevelItem::PLACETOWER) {
      TdBlockData data;
      data.levelItemType = TdLevelItem::PLACETOWER;
      data.blockNumber = i;
      data.isTowerPlacable = true;
      auto placeTower = std::make_shared<TdBlock>(
          *this, i * mLevelData->blockSize.x, j * mLevelData->blockSize.y, data,
          mLevelData->blockSize);
      for (auto g : getGameObjects()) {
        if (placeTower->isOverlapping(*g) &&
            g->tag() == TdRockThrowerTowerTag) {
          Mix_PlayChannel(
              1, ResourceManager::getInstance().getChunk(mSoundPath), 0);
          auto coinIndicatorVariable =
              mCoinIndicator.lock()
                  ->getGenericComponent<GameVariableComponent<int>>();
          coinIndicatorVariable->setVariable(
              coinIndicatorVariable->getVariable() + 5);
          removeObject(g);
          Mix_PlayChannel(1,
                          ResourceManager::getInstance().getChunk(
                              "TD2D/Audio/Common/Sell1.mp3"),
                          0);
          addObject(placeTower);
          currentlySelected = TdLevelItem::NONE;
          mGridObject.lock()->setCurrentlySelected("TD2D/Sprites/Tiles/Empty.png");

        }
      }
    }
  };

  gridObject->setGridCallBack(gridCallback);
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
                                                           int initialVal,
                                                           int x, int y) {
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
      return "TD2D/Sprites/Towers/cpix_towers/stone_throw_1.png";
    case TdLevelItem::ARROWTOWER:
      return "TD2D/Sprites/Towers/cpix_towers/arrow_tower_1.png";
    case TdLevelItem::MAGICTOWER:
      return "TD2D/Sprites/Towers/cpix_towers/aoe_tower_1.png";
    case TdLevelItem::ANTITANKMINE:
      return "TD2D/Sprites/Towers/cpix_towers/49.png";
    default:
      std::cerr << "Failed to get Graverunner block path for item "
                << static_cast<int>(item) << std::endl;
      return "";
  }
}
void TdLevel::spawnEnemy(TdLevelItem enemyType, int delay, int enemyNumber) {
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
    mNumEnemiesLeft--;
    // Increment the wave number if there are no enemies remaining
    if (mNumEnemiesLeft <= 0) {
      auto waveNumberVariable =
          mCurrentWaveNumberIndicator.lock()
              ->getGenericComponent<GameVariableComponent<int>>();
      waveNumberVariable->setVariable(waveNumberVariable->getVariable() + 1);
      mStartWaveButton.lock()->setIsVisibleOnScreen(true);
    }
  };
  // Actual constructor
  int pathIdx = enemyNumber % mLevelData.enemyPossiblePaths.size();
  std::shared_ptr<NonHostileEnemy> enemy = std::make_shared<NonHostileEnemy>(
      *this, mLevelData.blockSize.x * mLevelData.startPosition.x,
      mLevelData.blockSize.y * mLevelData.startPosition.y,
      mLevelData.blockSize.x, mLevelData.blockSize.y, enemyType,
      mLevelData.endPosition, mLevelData.levelGrid,
      mLevelData.enemyPossiblePaths[pathIdx],
      increaseScoreAndCoinsIndicatorLambda);
  // Decrease score and lives when reaching the end of the line
  auto decreaseScoreAndLivesIndicatorLambda =
      [=](Level& level, std::shared_ptr<GameObject> gameObject) {
        auto scoreVarComponent =
            mScoreIndicator.lock()
                ->getGenericComponent<GameVariableComponent<int>>();
        scoreVarComponent->setVariable(scoreVarComponent->getVariable() - 5);
        mNumEnemiesLeft--;
        if (mNumEnemiesLeft <= 0) {
          auto waveNumberVariable =
              mCurrentWaveNumberIndicator.lock()
                  ->getGenericComponent<GameVariableComponent<int>>();
          waveNumberVariable->setVariable(waveNumberVariable->getVariable() +
                                          1);
          mStartWaveButton.lock()->setIsVisibleOnScreen(true);
        }
      };
  enemy->addGenericComponent(std::make_shared<PerformHookOnCollideComponent>(
      *enemy, TdEndBlockTag, decreaseScoreAndLivesIndicatorLambda));
  enemy->addGenericComponent(
      std::make_shared<DelayedSpawnComponent>(*enemy, delay));
  addObject(enemy);
  mNumEnemiesLeft++;
}

void TdLevel::showTowerDetails() {
  mTowerDescText.lock()->setIsVisibleOnScreen(true);
  mTowerSellText.lock()->setIsVisibleOnScreen(true);
  mTowerFMText.lock()->setIsVisibleOnScreen(true);
  mFMClosestButton.lock()->setIsVisibleOnScreen(true);
  mFMFirstButton.lock()->setIsVisibleOnScreen(true);
  mFMLastButton.lock()->setIsVisibleOnScreen(true);
  mFMStrongestButton.lock()->setIsVisibleOnScreen(true);
}

void TdLevel::hideTowerDetails() {
  mTowerDescText.lock()->setIsVisibleOnScreen(false);
  mTowerSellText.lock()->setIsVisibleOnScreen(false);
  mTowerFMText.lock()->setIsVisibleOnScreen(false);
  mFMClosestButton.lock()->setIsVisibleOnScreen(false);
  mFMFirstButton.lock()->setIsVisibleOnScreen(false);
  mFMLastButton.lock()->setIsVisibleOnScreen(false);
  mFMStrongestButton.lock()->setIsVisibleOnScreen(false);
}
