#include "custom/NonHostileEnemy.hpp"

NonHostileEnemy::NonHostileEnemy(Level& level, float tl_x, float tl_y, float w,
                           float h, TdLevelItem enemyItem, Vector2D<int> targetPosition,
                           const std::vector<std::vector<TdBlockData>>& levelGrid,
                           std::vector<Vector2D<int>> possiblePath,
                           const std::function<void(void)>& callbackAtDeath)
    : CustomEnemy(level, tl_x, tl_y, w, h, enemyItem, 12, callbackAtDeath) {
  
  {
    // std::vector<std::vector<bool>> pathGrid;

    // // Resize and fill with default level items
    // pathGrid.resize(
    //     levelGrid.size(), std::vector<bool>(levelGrid[0].size()));

    // std::cout << "Path Grid:\n";

    // for (size_t i = 0; i < levelGrid.size(); i++)
    // {
    //   for (size_t j = 0; j < levelGrid[0].size(); j++)
    //   {
    //     if (3 <= (int)levelGrid[i][j].levelItemType && (int)levelGrid[i][j].levelItemType <= 13)
    //     {
    //       pathGrid[i][j] = true;
    //     } else {
    //       pathGrid[i][j] = false;
    //     }
    //     std::cout << std::to_string(pathGrid[i][j]) << " ";
    //   }
    //   std::cout << "\n";
    // }
  }
  
  // mRandomWalk = std::make_shared<RandomWalkComponent>(*this, pathGrid, targetPosition, Vector2D<int>(w, h), CustomEnemy::xVelocity);
  // addGenericComponent(mMoveTowards);

  //mMoveTowards = std::make_shared<MoveTowardsComponent>(*this, pathGrid, targetPosition, Vector2D<int>(w, h), CustomEnemy::xVelocity);
  //addGenericComponent(mMoveTowards);

  // Feed Path
  std::vector<float> Xs;
  std::vector<float> Ys;
  for (auto& checkpoint : possiblePath) {
    Xs.push_back(checkpoint.x * w);
    Ys.push_back(checkpoint.y * h);
  }

  mPatrol = std::make_shared<PatrolComponent>(*this, Xs, Ys, CustomEnemy::xVelocity);
  addGenericComponent(mPatrol);
}
