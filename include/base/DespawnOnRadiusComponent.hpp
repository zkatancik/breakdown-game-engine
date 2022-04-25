#ifndef DESPAWN_ON_RADIUS_COMPONENT_HPP
#define DESPAWN_ON_RADIUS_COMPONENT_HPP

#include <memory>

#include "GameObject.hpp"
#include "GenericComponent.hpp"
#include "PhysicsComponent.hpp"

//! \brief Component for keeping the GameObject's velocity constant across
//! frames
class DespawnOnRadius : public GenericComponent {
 public:
  DespawnOnRadius(GameObject &gameObject, float origX, float origY,
                  float radius)
      : GenericComponent(gameObject),
        mRadius(radius),
        mOrigX(origX),
        mOrigY(origY) {}

  void update(Level &level) override {
    auto gameObject = getGameObject().shared_from_this();

    if (gameObject->x() >= mOrigX + mRadius ||
        gameObject->x() <= mOrigX - mRadius ||
        gameObject->y() >= mOrigY + mRadius ||
        gameObject->y() <= mOrigY - mRadius) {
         level.removeObject(gameObject);
    }
  }

 private:
  float mRadius;
  float mOrigX;
  float mOrigY;
};
#endif