#include "base/MoveTowardsComponent.hpp"
#include "base/GameObject.hpp"
#include <cmath>

MoveTowardsComponent::MoveTowardsComponent(GameObject & gameObject, std::vector<std::vector<bool>> pg,
   Vector2D<int> tp, float speed):
  GenericComponent(gameObject),
  pathGrid(pg),
  targetPosition(tp),
  currIter(0),
  speed(speed)
{
  nextGridPosition = Vector2D<int>(-1, -1);
}

void
MoveTowardsComponent::update(Level & level)
{
  GameObject & gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  float xCurr = gameObject.x() + 32;
  float yCurr = gameObject.y() + 32;

  int xCurrOnGrid = round(yCurr) / 64; 
  int yCurrOnGrid = round(xCurr) / 64;

  // Cue Path planning.
  if ((prevGridPositions.size() == 0) 
      || (((nextGridPosition.y * 64) + 32 - 1.5 <= xCurr && xCurr <= (nextGridPosition.y * 64) + 32 + 1.5) 
          && 
          ((nextGridPosition.x * 64) + 32 - 1.5 <= yCurr && yCurr <= (nextGridPosition.x * 64) + 32 + 1.5)))
  {
    if (InBounds(xCurrOnGrid,yCurrOnGrid + 1)
      && !(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>(xCurrOnGrid, (yCurrOnGrid + 1))) != prevGridPositions.end())
      && pathGrid[xCurrOnGrid][yCurrOnGrid + 1])
    {
      // North
      nextGridPosition.x = xCurrOnGrid;
      nextGridPosition.y = yCurrOnGrid + 1;
    } else if (InBounds(xCurrOnGrid,yCurrOnGrid - 1) 
      && !(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>(xCurrOnGrid, (yCurrOnGrid - 1))) != prevGridPositions.end())
      && pathGrid[xCurrOnGrid][yCurrOnGrid - 1]) {
      // South
      nextGridPosition.x = xCurrOnGrid;
      nextGridPosition.y = yCurrOnGrid - 1;
    } else if (InBounds(xCurrOnGrid + 1,yCurrOnGrid) 
      && !(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>((xCurrOnGrid + 1), yCurrOnGrid)) != prevGridPositions.end())
      && pathGrid[xCurrOnGrid + 1][yCurrOnGrid]) {
      // East
      nextGridPosition.x = xCurrOnGrid + 1;
      nextGridPosition.y = yCurrOnGrid;
    } else if (InBounds(xCurrOnGrid - 1,yCurrOnGrid) 
      && !(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>((xCurrOnGrid - 1), yCurrOnGrid)) != prevGridPositions.end())
      && pathGrid[xCurrOnGrid - 1][yCurrOnGrid]) {
      // West
      nextGridPosition.x = xCurrOnGrid - 1;
      nextGridPosition.y = yCurrOnGrid;
    }
  }
  int x2F = (nextGridPosition.y * 64) + 32;
  int y2F = (nextGridPosition.x * 64) + 32;

  float deltaX = x2F - xCurr;
  float deltaY = y2F - yCurr;
  pc->setVx(speed * (deltaX / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));
  pc->setVy(speed * (deltaY / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));

  if (!(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>((xCurrOnGrid), yCurrOnGrid)) != prevGridPositions.end()))
  {
    prevGridPositions.push_back(Vector2D<int>(xCurrOnGrid, yCurrOnGrid));
  }
}

bool MoveTowardsComponent::GetDirection() {
  GameObject & gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  return pc->vx() > 0;
}

bool MoveTowardsComponent::InBounds(int x, int y) {
  return (x >= 0 && x < pathGrid.size()) 
    &&
    (y >= 0 && y < pathGrid[0].size());
}