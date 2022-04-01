#include "graverunner/FollowerZombie.hpp"

FollowerZombie::FollowerZombie(Level &level): BaseEnemy(level) {
  
}

void FollowerZombie::startUp(float tl_x, float tl_y, float w, float h,
                         std::vector<std::pair<float, float>>& checkpoints, std::shared_ptr<Jack> j) {
  BaseEnemy::startUp(tl_x, tl_y, w, h, checkpoints, j);

  std::vector<float> Xs;
  std::vector<float> Ys;
  for (auto & checkpoint : checkpoints) {
    Xs.push_back(checkpoint.first);
    Ys.push_back(checkpoint.second);
  }

  mFollower = std::make_shared<FollowComponent>(*this, Xs, Ys, BaseEnemy::xVelocity, j);
  addGenericComponent(mFollower);
}

