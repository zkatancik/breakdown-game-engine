#include "graverunner/PatrolZombie.hpp"

PatrolZombie::PatrolZombie(Level& level, float tl_x, float tl_y, float w,
                           float h,
                           std::vector<std::pair<float, float>>& checkpoints,
                           std::shared_ptr<Jack> j)
    : BaseEnemy(level, tl_x, tl_y, w, h, checkpoints, j) {
  std::vector<float> Xs;
  std::vector<float> Ys;
  for (auto& checkpoint : checkpoints) {
    Xs.push_back(checkpoint.first);
    Ys.push_back(checkpoint.second);
  }
  mPatrol =
      std::make_shared<PatrolComponent>(*this, Xs, Ys, BaseEnemy::xVelocity);
  addGenericComponent(mPatrol);
}
