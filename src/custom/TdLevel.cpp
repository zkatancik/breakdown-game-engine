#include "custom/TdLevel.hpp"

#include <box2d/b2_body.h>

#include "base/GameVariableComponent.hpp"
#include "base/PerformHookOnCollideComponent.hpp"
#include "custom/LevelData.hpp"
#include "custom/Tag.hpp"
#include "custom/TdBlock.hpp"

void TdLevel::initialize() {
  TdLevelData levelData;
  loadLevel(&levelData, currentLevelNumber);

  int rowsOfBlocks = levelData.rowCount;
  int blocksPerRow = levelData.colCount;
  Vector2D<int> blockSize = levelData.blockSize;

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
      
      auto b = levelData.levelGrid[i][j];
      auto placeableBlocks = levelData.placableBlockGrid[i][j];

      // Level File.
      if (b.levelItemType != TdLevelItem::NOBLOCK) {
        std::shared_ptr<GameObject> obj;

        if (b.levelItemType == TdLevelItem::PLAINBLOCK) {
          obj = std::make_shared<TdBlock>(*this, x, y, b, blockSize);
        } else if (b.levelItemType == TdLevelItem::PATHBLOCK) {
          obj = std::make_shared<TdBlock>(*this, x, y, b, blockSize);
        }

        addObject(obj);
      }

      // Tower Map items (Placeablegrid).
      if (placeableBlocks.levelItemType != TdLevelItem::NOBLOCK) {
        std::shared_ptr<GameObject> placeableObj;

        if (placeableBlocks.levelItemType == TdLevelItem::PLACETOWER) {
          placeableObj = std::make_shared<TdBlock>(*this, x, y, placeableBlocks, blockSize);
        } else if (placeableBlocks.levelItemType == TdLevelItem::START) {
          placeableObj = std::make_shared<TdBlock>(*this, x, y, placeableBlocks, blockSize);
        } else if (placeableBlocks.levelItemType == TdLevelItem::END) {
          placeableObj = std::make_shared<TdBlock>(*this, x, y, placeableBlocks, blockSize);
        }

        addObject(placeableObj);
      }

      x = x + blockSize.x;
    }
    count++;
    y = y + blockSize.y;
  }
}

bool TdLevel::isLevelWon() const {
  //TODO- add real win condition
  return false;
}

bool TdLevel::isLevelInProgress() const {
  //TODO- add real inprogress condition
  return true;
}

std::shared_ptr<GameObject> TdLevel::createLevelIndicatorObject() {
  auto levelIndicator =
      std::make_shared<GameObject>(*this, 10, 10, 50, 50, BaseTextTag);
  auto textRenderer =
  std::make_shared<TextureRenderComponent>(*levelIndicator);

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
  //TODO- use a font from TD2D (and/or move one from another game)
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
