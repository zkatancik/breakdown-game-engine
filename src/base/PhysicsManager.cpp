#include "base/PhysicsManager.hpp"
#include "base/GameObject.hpp"

PhysicsManager &
PhysicsManager::getInstance()
{
  static PhysicsManager * instance = new PhysicsManager();
  return *instance;
}

void
PhysicsManager::startUp()
{
  mWorld = new b2World(b2Vec2(0.0f, 0.0f));
}

void
PhysicsManager::shutDown()
{
  delete mWorld;
  mWorld = nullptr;
}

void
PhysicsManager::step()
{
  if (mWorld == nullptr)
    return;
  const float timeStep = 1.0f / 60.0f;
  const int velocityIterations = 6;
  const int positionIterations = 2;

  mWorld->Step(timeStep, velocityIterations, positionIterations);

  // TODO PART3: notify objects of any collisions

  b2Contact * contact =  mWorld->GetContactList();
  while (contact) {
    if (contact->IsTouching()) {
      b2Body * bodyA = contact->GetFixtureA()->GetBody();
      b2Body * bodyB = contact->GetFixtureB()->GetBody();

      GameObject * goA = reinterpret_cast<GameObject *>(bodyA->GetUserData().pointer);
      GameObject * goB = reinterpret_cast<GameObject *>(bodyB->GetUserData().pointer);

      goA->collision(goB->shared_from_this());
      goB->collision(goA->shared_from_this());
    }

    contact = contact->GetNext();
  }
}

// TODO PART4: subclass b2QueryCallback
class PhysicsCallBack : public b2QueryCallback {
public:
  PhysicsCallBack(std::vector<std::shared_ptr<GameObject>> & objects):
    mObjects(objects)
  {
  }

  virtual bool ReportFixture(b2Fixture * fixture) override {
    b2Body * body = fixture->GetBody();
    GameObject * go = reinterpret_cast<GameObject *>(body->GetUserData().pointer);
    mObjects.push_back(go->shared_from_this());
    return true;
  }

private:
  std::vector<std::shared_ptr<GameObject>> & mObjects;
};

bool
PhysicsManager::getCollisions(float rx, float ry, float rw, float rh, std::vector<std::shared_ptr<GameObject>> & objects) const
{
  b2AABB box;
  box.lowerBound.Set(
    rx * PhysicsManager::GAME_TO_PHYSICS_SCALE,
    ry * PhysicsManager::GAME_TO_PHYSICS_SCALE);

  box.upperBound.Set(
    (rx + rw) * PhysicsManager::GAME_TO_PHYSICS_SCALE,
    (ry + rh) * PhysicsManager::GAME_TO_PHYSICS_SCALE);

  objects.clear();
  PhysicsCallBack callback(objects);
  mWorld->QueryAABB(&callback, box);

  return !objects.empty();
}
