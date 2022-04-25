#include "editor/TdEnemyEditor.hpp"

#include "custom/LevelData.hpp"
#include "custom/Tag.hpp"

#include "base/Collection.hpp"
#include "base/UICounter.hpp"



class EnemyCounter : public Collection {
 public:
  EnemyCounter(Level& level, float x, float y, Vector2D<int> blockSize, TdLevelItem enemyItem, int number) : Collection(level), mEnemyItem(enemyItem) {
    // Enemy icon

    auto button = std::make_shared<LevelEditButton>(
        level, x, y - 20, 64, 64, 5, 5, getEnemySpritePath(enemyItem) + "0.png", "TD2D/Audio/Common/Click1.mp3", []{}, true);
    level.addObject(button);
    // Add counter
    mCounter = std::make_shared<UICounter>(level, x + 100, y, number);
  }

  int getCount() {
    return mCounter->getCounterValue();
  }

  TdLevelItem getEnemyItem() {return mEnemyItem;}

 private:
  std::shared_ptr<UICounter> mCounter;
  std::shared_ptr<GameObject> mEnemyIcon;
  TdLevelItem mEnemyItem;
};


void TdEnemyEditor::initialize() {
  loadLevel(&mLevelData, mLevelNumber);
  // Add buttons here:

  int y = 10;
  for (size_t i = 0; i < mLevelData.enemyWaves.size(); i++) {
    // Add wave label
    auto label = std::make_shared<GameObject>(*this, 2, y, 50, 50, BaseTextTag);
    auto textRenderer = std::make_shared<TextureRenderComponent>(*label);

    textRenderer->setRenderMode(TextureRenderComponent::RenderMode::QUERY);
    label->setRenderComponent(textRenderer);
    std::string levelMessage = "Wave " + std::to_string(i);
    auto textComponent = std::make_shared<TextComponent>(
        *label, levelMessage, 32, "TD2D/Fonts/madera-tygra.ttf",
        textRenderer);
    label->addGenericComponent(textComponent);
    addObject(label);
    int x = 150;
    for (int j = 0; j < itemVector.size(); j++) {
      auto it = mLevelData.enemyWaves[i].find(itemVector[j]);
      if (it != mLevelData.enemyWaves[i].end())
        std::cout << it->second << std::endl;
      auto button = std::make_shared<EnemyCounter>(*this, x, y, mLevelData.blockSize, itemVector[j],
                                                   (it != mLevelData.enemyWaves[i].end()) ? it->second : 0);
      x = x + 250;
      if ((j + 1) % 5 == 0) {
        x = 150;
        y += 80;
      }
    }
  }
}

void TdEnemyEditor::refreshLevelEditor() {
//
//  for (const auto& gameObject : getGameObjects()) {
//    // Remove any blocks remaining previously
//    if (gameObject->tag() == TdRockThrowerTowerTag ||
//        gameObject->tag() == TdEndBlockTag ||
//        gameObject->tag() == TdBlockTag ||
//        gameObject->tag() == TdBGTag ||
//        gameObject->tag() == TdEnemyTag ||
//        gameObject->tag() == TdBulletTag ||
//        gameObject->tag() == TdStartWaveButtonTag ||
//        gameObject->tag() == TdEditButtonTag ||
//        gameObject->tag() == TdToolbarTag ||
//        gameObject->tag() == BaseTextTag)
//      removeObject(gameObject);
//  }
//
//  TdLevel::initialize();
//  // Strip away unwanted things for rendering in level editor
//  for (const auto& gameObject : getGameObjectsToAdd()) {
//    // Remove any text components (lives, level, score, etc) + Ball + Paddle +
//    // Boundaries
//    if (
//        gameObject->tag() == TdRockThrowerTowerTag ||
//        gameObject->tag() == TdEndBlockTag ||
//        gameObject->tag() == TdBlockTag ||
//        gameObject->tag() == TdBGTag ||
//        gameObject->tag() == BaseTextTag
//      ) {
//        // Add an x-offset to make space for buttons
//        gameObject->setX(gameObject->x() + float(xOffset));
//      } else if (
//        gameObject->tag() == TdEnemyTag ||
//        gameObject->tag() == TdBulletTag ||
//        gameObject->tag() == TdStartWaveButtonTag ||
//        gameObject->tag() == TdEditButtonTag ||
//        gameObject->tag() == TdToolbarTag
//      ) {
//        gameObject->setIsVisibleOnScreen(false);
//        removeObject(gameObject);
//      }
//  }
//
//  // Read in the level data for our own usage
//  loadLevel(&mLevelData, getLevelNumber());
//
}
