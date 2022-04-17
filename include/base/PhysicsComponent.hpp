#ifndef BASE_PHYSICS_COMPONENT
#define BASE_PHYSICS_COMPONENT

#include "base/Component.hpp"
#include "box2d/box2d.h"
#include <tuple>

class Level;

//! \brief A component for handling physics.
class PhysicsComponent : public Component {
 public:
  enum class Type { DYNAMIC_SOLID, STATIC_SOLID, STATIC_SENSOR };

  PhysicsComponent(GameObject &gameObject, b2BodyType type, bool isSensor,
                   float linearDamping = 2.0f, float density = 1.0,
                   float restitution = 0.0, float friction = 0.0);

  PhysicsComponent(GameObject &gameObject, b2BodyDef bodyDef, b2FixtureDef fixtureDef, b2PolygonShape polygonShape);

  virtual ~PhysicsComponent();

  inline std::tuple<b2BodyDef, b2FixtureDef, b2PolygonShape> getBodyDef() {
    return std::make_tuple(mBodyDef, mFixtureDef, mPolygonShape);
  }

  void setVx(float vx);  //!< set x velocity
  void setVy(float vy);  //!< set y velocity

  float vx() { return mBody->GetLinearVelocity().x; };  //!< get x velocity
  float vy() { return mBody->GetLinearVelocity().y; };  //!< get y velocity
  float x() {
    return mBody->GetPosition().x;
  }  //!< get x position of the physics body. Not equal to the pixel position
     //!< from GameObject
  float y() {
    return mBody->GetPosition().y;
  }  //!< get y position of the physics body. Not equal to the pixel position
     //!< from GameObject

  void addFx(float fx);  //!< add force in x direction
  void addFy(float fy);  //!< add force in y direction

  void postStep();  //!< Called after physics step.

 private:
  b2BodyDef mBodyDef;
  b2FixtureDef mFixtureDef;
  b2PolygonShape mPolygonShape;
  b2Body *mBody{nullptr};
};

#endif