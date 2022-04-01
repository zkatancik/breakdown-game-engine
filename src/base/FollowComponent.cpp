#include "base/FollowComponent.hpp"
#include "base/GameObject.hpp"
#include <cmath>

FollowComponent::FollowComponent(GameObject & gameObject, std::vector<float> Xs, std::vector<float> Ys, float speed, std::shared_ptr<Jack> j):
  GenericComponent(gameObject),
  Xs(std::move(Xs)),
  Ys(std::move(Ys)),
  currIter(0),
  speed(speed),
  jack(j)
{
  this->Xs.insert(this->Xs.begin(), getGameObject().x());
  this->Ys.insert(this->Ys.begin(), getGameObject().y());
}

void
FollowComponent::update(Level & level)
{
  GameObject & gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  pc->addFy(mGravityForce);

  float xCurr = gameObject.x();
  float yCurr = gameObject.y();

  // Xs.at(currIter != Xs.size() - 1 ? currIter + 1 : 0);
  // Ys.at(currIter != Ys.size() - 1 ? currIter + 1 : 0);
  float x2 = jack->x();
  float y2 = jack->y();

  float deltaX = x2 - xCurr;
  float deltaY = y2 - yCurr;
  pc->setVx(speed * (deltaX / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));
  //pc->setVy(speed * (deltaY / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));

  if (std::abs(xCurr - x2) < speed / 60. && std::abs(yCurr - y2) < speed / 60.) {
    currIter = currIter != Xs.size() - 1 ? currIter + 1 : 0;
  }
}

bool FollowComponent::GetDirection() {
  GameObject & gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  return pc->vx() > 0;
}
