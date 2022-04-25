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
    GameObject &gameObject = getGameObject();
    // std::shared_ptr<GameObject> gameObjectPointer =
    //     std::make_shared<GameObject>(gameObject);

    if (gameObject.x() >= mOrigX + mRadius ||
        gameObject.x() <= mOrigX - mRadius ||
        gameObject.y() >= mOrigY + mRadius ||
        gameObject.y() <= mOrigY - mRadius) {
      gameObject.setIsVisibleOnScreen(false);
      //   std::shared_ptr<GameObject> gameObjectPointer =
      //       std::make_shared<GameObject>(std::move(gameObject));
      //   level.removeObject(gameObject);
    }
  }

 private:
  float mRadius;
  float mOrigX;
  float mOrigY;
};
#endif