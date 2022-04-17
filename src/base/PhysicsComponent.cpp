#include "base/PhysicsComponent.hpp"

#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/PhysicsManager.hpp"

PhysicsComponent::PhysicsComponent(GameObject& gameObject, b2BodyType type,
                                   bool isSensor, float linearDamping,
                                   float density, float restitution,
                                   float friction)
    : Component(gameObject) {
  if (PhysicsManager::getInstance().hasStarted()) {
    mBodyDef = b2BodyDef();
    mBodyDef.type = type;
    mBodyDef.position.x = (gameObject.x() + 0.5f * gameObject.w()) *
                         PhysicsManager::GAME_TO_PHYSICS_SCALE;
    mBodyDef.position.y = (gameObject.y() + 0.5f * gameObject.h()) *
                         PhysicsManager::GAME_TO_PHYSICS_SCALE;
    mBodyDef.linearDamping = linearDamping;
    mBodyDef.fixedRotation = true;
    mBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(&gameObject);
    mBody = PhysicsManager::getInstance().getWorld()->CreateBody(&mBodyDef);

    mPolygonShape = b2PolygonShape();
    mPolygonShape.SetAsBox(
        0.495 * gameObject.w() * PhysicsManager::GAME_TO_PHYSICS_SCALE,
        0.495 * gameObject.h() *
            PhysicsManager::GAME_TO_PHYSICS_SCALE);  // a 4x2 rectangle

    mFixtureDef = b2FixtureDef();
    mFixtureDef.shape = &mPolygonShape;
    mFixtureDef.restitution = restitution;
    mFixtureDef.friction = friction;
    mFixtureDef.isSensor = isSensor;
    mFixtureDef.density =
        (type == b2_dynamicBody || type == b2_kinematicBody) ? density : 0.0;

    mBody->CreateFixture(&mFixtureDef);
  }
}

PhysicsComponent::PhysicsComponent(GameObject &gameObject,
                                   b2BodyDef bodyDef,
                                   b2FixtureDef fixtureDef,
                                   b2PolygonShape polygonShape) : Component(gameObject), mBodyDef(bodyDef),
                                   mFixtureDef(fixtureDef), mPolygonShape(polygonShape) {
  if (PhysicsManager::getInstance().hasStarted()) {
    mBody = PhysicsManager::getInstance().getWorld()->CreateBody(&mBodyDef);
    mFixtureDef.shape = &mPolygonShape;
    mBody->CreateFixture(&mFixtureDef);
  }
}

PhysicsComponent::~PhysicsComponent() {
  if (mBody != nullptr) {
    PhysicsManager::getInstance().getWorld()->DestroyBody(mBody);
    mBody = nullptr;
  }
}

void PhysicsComponent::setVx(float vx) {
  if (mBody != nullptr)
    mBody->SetLinearVelocity(b2Vec2(vx * PhysicsManager::GAME_TO_PHYSICS_SCALE,
                                    mBody->GetLinearVelocity().y));
}

void PhysicsComponent::setVy(float vy) {
  if (mBody != nullptr)
    mBody->SetLinearVelocity(
        b2Vec2(mBody->GetLinearVelocity().x,
               vy * PhysicsManager::GAME_TO_PHYSICS_SCALE));
}

void PhysicsComponent::addFx(float fx) {
  if (mBody != nullptr)
    mBody->ApplyForce(b2Vec2(fx * PhysicsManager::GAME_TO_PHYSICS_SCALE, 0.0f),
                      mBody->GetPosition(), true);
}

void PhysicsComponent::addFy(float fy) {
  if (mBody != nullptr)
    mBody->ApplyForce(b2Vec2(0.0f, fy * PhysicsManager::GAME_TO_PHYSICS_SCALE),
                      mBody->GetPosition(), true);
}

void PhysicsComponent::postStep() {
  if (mBody != nullptr) {
    b2Vec2 position = mBody->GetPosition();

    GameObject& gameObject = getGameObject();

    gameObject.setX(position.x / PhysicsManager::GAME_TO_PHYSICS_SCALE -
                    0.5f * gameObject.w());
    gameObject.setY(position.y / PhysicsManager::GAME_TO_PHYSICS_SCALE -
                    0.5f * gameObject.h());
  }
}
