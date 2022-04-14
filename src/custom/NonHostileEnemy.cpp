#include "custom/NonHostileEnemy.hpp"

NonHostileEnemy::NonHostileEnemy(Level& level, float tl_x, float tl_y, float w,
                           float h, std::string spritePath, TdLevelItem enemyItem,
                           Vector2D<int> targetPosition)
    : CustomEnemy(level, tl_x, tl_y, w, h, spritePath, enemyItem) {
  
  mMoveTowards = std::make_shared<MoveTowardsComponent>(*this, targetPosition, CustomEnemy::xVelocity);
  addGenericComponent(mMoveTowards);
}
