#include "custom/NonHostileEnemy.hpp"

NonHostileEnemy::NonHostileEnemy(Level& level, float tl_x, float tl_y, float w,
                           float h, std::string spritePath, TdLevelItem enemyItem,
                           Vector2D<int> targetPosition,
                           const std::vector<std::vector<TdBlockData>>& levelGrid)
    : CustomEnemy(level, tl_x, tl_y, w, h, spritePath, enemyItem) {
  
  std::vector<std::vector<bool>> pathGrid;

  // Resize and fill with default level items
  pathGrid.resize(
      levelGrid.size(), std::vector<bool>(levelGrid[0].size()));

  for (size_t i = 0; i < levelGrid.size(); i++)
  {
    for (size_t j = 0; j < levelGrid[0].size(); j++)
    {
      if (levelGrid[i][j].levelItemType == TdLevelItem::PATHBLOCK)
      {
        pathGrid[i][j] = true;
      } else {
        pathGrid[i][j] = false;
      }
    }
  }
  

  mMoveTowards = std::make_shared<MoveTowardsComponent>(*this, pathGrid, targetPosition, CustomEnemy::xVelocity);
  addGenericComponent(mMoveTowards);
}
