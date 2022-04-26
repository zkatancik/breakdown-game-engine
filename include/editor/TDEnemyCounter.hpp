#ifndef EDITOR_TD_ENEMY_COUNTER
#define EDITOR_TD_ENEMY_COUNTER
#include "base/Collection.hpp"

class EnemyCounter : public Collection {
 public:
  EnemyCounter(Level& level, float x, float y, Vector2D<int> blockSize, TdLevelItem enemyItem, int number) : Collection(level), mEnemyItem(enemyItem) {
    // Enemy icon

    auto button = std::make_shared<LevelEditButton>(
        level, x, y - 20, 64, 64, 5, 5, getEnemySpritePath(enemyItem) + "0.png", "TD2D/Audio/Common/Click1.mp3", []{}, true);
    addGameObject(button);
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


#endif