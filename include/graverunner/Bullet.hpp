#ifndef BULLET_HPP
#define BULLET_HPP
#include "graverunner/GraveRunnerLevel.hpp"
#include "base/GameObject.hpp"

/**
 * @brief Jack fires bullets!
 */
class Bullet : public GameObject {
  public:
    explicit Bullet(Level& level, float x, float y, float w, float h, bool isFacingLeft);
    void update() override;
  private:
    float velocity = 400;
};

#endif