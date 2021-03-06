#include "base/PatrolComponent.hpp"
#include "base/GameObject.hpp"
#include <cmath>

PatrolComponent::PatrolComponent(GameObject & gameObject, std::vector<float> Xs, std::vector<float> Ys, float speed):
  GenericComponent(gameObject),
  Xs(std::move(Xs)),
  Ys(std::move(Ys)),
  currIter(0),
  speed(speed)
{
  this->Xs.insert(this->Xs.begin(), getGameObject().x());
  this->Ys.insert(this->Ys.begin(), getGameObject().y());
}

void
PatrolComponent::update(Level & level)
{
  GameObject & gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  float xCurr = gameObject.x();
  float yCurr = gameObject.y();

  float x2 = Xs.at(currIter != Xs.size() - 1 ? currIter + 1 : 0);
  float y2 = Ys.at(currIter != Ys.size() - 1 ? currIter + 1 : 0);

  float deltaX = x2 - xCurr;
  float deltaY = y2 - yCurr;
  pc->setVx(speed * (deltaX / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));
  pc->setVy(speed * (deltaY / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));

  if (std::abs(xCurr - x2) < speed / 60. && std::abs(yCurr - y2) < speed / 60.) {
    currIter = currIter != Xs.size() - 1 ? currIter + 1 : 0;
  }
}

bool PatrolComponent::GetDirection() {
  GameObject & gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  return pc->vx() > 0;
}
