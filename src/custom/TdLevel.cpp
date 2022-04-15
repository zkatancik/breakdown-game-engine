#include "custom/TdLevel.hpp"

#include <box2d/b2_body.h>

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

void TdLevel::initialize() {
  loadLevel(&mLevelData, currentLevelNumber);

  int rowsOfBlocks = mLevelData.rowCount;
  int blocksPerRow = mLevelData.colCount;
  Vector2D<int> blockSize = mLevelData.blockSize;

  // Create indicators
  auto keysIndicator = createScoreIndicatorObject();
  auto levelIndicator = createLevelIndicatorObject();
  addObject(levelIndicator);
  addObject(keysIndicator);

  auto background =
      std::make_shared<GameObject>(*this, 0, 0, 1280, 768, TdBGTag);
  auto bg_renderer = std::make_shared<TextureRenderComponent>(*background);

  // All-green background
  bg_renderer->setRenderMode(TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  background->setRenderComponent(bg_renderer);
  bg_renderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/Maps/Backgrounds/TileMap1.png"));
  addObject(background);

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

  // Place Enemies end points
  std::shared_ptr<NonHostileEnemy> enemy = std::make_shared<NonHostileEnemy>(
      *this, blockSize.x * mLevelData.startPosition.x,
      blockSize.y * mLevelData.startPosition.y, blockSize.x, blockSize.y,
      "4/4_enemies_1_run_", TdLevelItem::SCORPIONS, mLevelData.endPosition, mLevelData.levelGrid);
  addObject(enemy);

  createSidebarControls();
  createBottomBarControls();
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
      std::make_shared<GameObject>(*this, mScreenWidth - xOffset, 0, xOffset,
                                   mScreenHeight, hash("ToolbarTag"));
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
    mGridObject->setCurrentlySelected("ERASE");
  };

  auto eraseButton = std::make_shared<LevelEditButton>(
      *this, (mScreenWidth - xOffset) + 109, 35, 74, 74, 5, 5,
      "2DBreakout/Graphics/"
      "erase.png",
      mSoundPath, changeToErase);

  addObject(eraseButton);

  int x = (mScreenWidth - xOffset) + 20;
  int y = 193;
  int count = 0;

  for (const auto& item : itemVector) {
    auto lambda = [&] {
      currentlySelected = item;
      mGridObject->setCurrentlySelected(getTdBlockPath(item));
    };
    auto button = std::make_shared<LevelEditButton>(*this, x, y, 74, 74, 5.f,
                                                    5.f, getTdBlockPath(item),
                                                    mSoundPath, lambda, true);
    addObject(button);
    x = x + 89;
    count++;
    if (count == 2) {
      y = y + 79;
      x = (mScreenWidth - xOffset) + 20;
      count = 0;
    }
  }
}

void TdLevel::createBottomBarControls() {
  auto toolbarBackground = std::make_shared<GameObject>(
      *this, 0, mScreenHeight - yOffset, mScreenWidth - xOffset, yOffset,
      hash("ToolbarTag"));
  auto backgroundRenderer =
      std::make_shared<TextureRenderComponent>(*toolbarBackground);

  backgroundRenderer->setRenderMode(
      TextureRenderComponent::RenderMode::WHOLE_WIDTH);
  toolbarBackground->setRenderComponent(backgroundRenderer);
  backgroundRenderer->setTexture(ResourceManager::getInstance().getTexture(
      "TD2D/Sprites/GUI/Menu/bottombar.png"));

  addObject(toolbarBackground);
}

void TdLevel::createGrid() {
  auto gridCallback = [&, mLevelData = &mLevelData](int i, int j) {
    if (currentlySelected != TdLevelItem::NONE) {
      Mix_PlayChannel(1, ResourceManager::getInstance().getChunk(mSoundPath),
                      0);
      // updateCurrentLevel(mLevelData, Vector2D<int>(i, j), currentlySelected);
    }
  };

  mGridObject =
      std::make_shared<GridObject>(*this, 0, 0, 20, 12, 64, 64, gridCallback,
                                   getTdBlockPath(currentlySelected));
  addObject(mGridObject);
}

std::shared_ptr<GameObject> TdLevel::createLevelIndicatorObject() {
  auto levelIndicator =
      std::make_shared<GameObject>(*this, 10, 10, 50, 50, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*levelIndicator);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  levelIndicator->setRenderComponent(textRenderer);
  std::string levelMessage = "Level: " + std::to_string(currentLevelNumber);
  auto textComponent = std::make_shared<TextComponent>(
      *levelIndicator, levelMessage, 32, "Graverunner/fonts/GADAQUALI.ttf",
      textRenderer);
  levelIndicator->addGenericComponent(textComponent);
  return levelIndicator;
}

std::shared_ptr<GameObject> TdLevel::createScoreIndicatorObject() {
  auto scoreIndicator =
      std::make_shared<GameObject>(*this, 10, 50, 50, 50, BaseTextTag);
  auto textRenderer = std::make_shared<TextureRenderComponent>(*scoreIndicator);

  textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
  scoreIndicator->setRenderComponent(textRenderer);
  std::string levelMessage = "Score: 0";
  // TODO- use a font from TD2D (and/or move one from another game)
  auto textComponent = std::make_shared<TextComponent>(
      *scoreIndicator, levelMessage, 32, "Graverunner/fonts/GADAQUALI.ttf",
      textRenderer);
  scoreIndicator->addGenericComponent(textComponent);
  auto gameVariableComponent =
      std::make_shared<GameVariableComponent<int>>(*scoreIndicator, 0);
  scoreIndicator->addGenericComponent(gameVariableComponent);
  std::weak_ptr<GameVariableComponent<int>> gameVariableComponentWeak(
      gameVariableComponent);
  std::weak_ptr<TextComponent> textComponentWeak(textComponent);
  gameVariableComponent->setUpdateCallBack(
      [gameVariableComponentWeak, textComponentWeak] {
        textComponentWeak.lock()->SetMText(
            "Score: " +
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
