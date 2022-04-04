#include "base/PhysicsComponent.hpp"
#include "base/PhysicsManager.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"

PhysicsComponent::PhysicsComponent(GameObject & gameObject, b2BodyType type, bool isSensor, float linearDamping, float density):
Component(gameObject)
{
  if (PhysicsManager::getInstance().hasStarted()) {
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.x = (gameObject.x() + 0.5f * gameObject.w()) * PhysicsManager::GAME_TO_PHYSICS_SCALE;
    bodyDef.position.y = (gameObject.y() + 0.5f * gameObject.h()) * PhysicsManager::GAME_TO_PHYSICS_SCALE;
    bodyDef.linearDamping = linearDamping;
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(&gameObject);
    mBody = PhysicsManager::getInstance().getWorld()->CreateBody(&bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(
        0.495 * gameObject.w() * PhysicsManager::GAME_TO_PHYSICS_SCALE,
        0.495 * gameObject.h() * PhysicsManager::GAME_TO_PHYSICS_SCALE)
        ; //a 4x2 rectangle

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygonShape;
        fixtureDef.friction = 0.0f;
        fixtureDef.isSensor = isSensor;
        fixtureDef.density = (type == b2_dynamicBody || type == b2_kinematicBody) ? density : 0.0 ;

        mBody->CreateFixture(&fixtureDef);
  }
}

PhysicsComponent::~PhysicsComponent()
{
  if (mBody != nullptr) {
    PhysicsManager::getInstance().getWorld()->DestroyBody(mBody);
    mBody = nullptr;
  }
}

void
PhysicsComponent::setVx(float vx)
{
  if (mBody != nullptr)
    mBody->SetLinearVelocity(b2Vec2(vx * PhysicsManager::GAME_TO_PHYSICS_SCALE, mBody->GetLinearVelocity().y));
}

void
PhysicsComponent::setVy(float vy)
{
  if (mBody != nullptr)
    mBody->SetLinearVelocity(b2Vec2(mBody->GetLinearVelocity().x, vy * PhysicsManager::GAME_TO_PHYSICS_SCALE));
}

void
PhysicsComponent::addFx(float fx)
{
  if (mBody != nullptr)
    mBody->ApplyForce(b2Vec2(fx * PhysicsManager::GAME_TO_PHYSICS_SCALE, 0.0f), mBody->GetPosition(), true);
}

void
PhysicsComponent::addFy(float fy)
{
  if (mBody != nullptr)
  mBody->ApplyForce(b2Vec2(0.0f, fy * PhysicsManager::GAME_TO_PHYSICS_SCALE), mBody->GetPosition(), true);
}



void
PhysicsComponent::postStep()
{
  if (mBody != nullptr) {
    b2Vec2 position = mBody->GetPosition();

    GameObject & gameObject = getGameObject();

    gameObject.setX(position.x / PhysicsManager::GAME_TO_PHYSICS_SCALE - 0.5f * gameObject.w());
    gameObject.setY(position.y / PhysicsManager::GAME_TO_PHYSICS_SCALE - 0.5f * gameObject.h());
  }
}
