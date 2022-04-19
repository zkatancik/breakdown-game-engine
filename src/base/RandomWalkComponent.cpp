#include "base/RandomWalkComponent.hpp"
#include "base/GameObject.hpp"
#include <cmath>

RandomWalkComponent::RandomWalkComponent(GameObject & gameObject, std::vector<std::vector<bool>> pg,
   Vector2D<int> tp, Vector2D<int> bs, float speed):
  GenericComponent(gameObject),
  pathGrid(pg),
  targetPosition(tp),
  blockSize(bs),
  currIter(0),
  speed(speed)
{
  nextGridPosition = Vector2D<int>(-1, -1);
}

void
RandomWalkComponent::update(Level & level)
{
  GameObject & gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  float xCurr = gameObject.x() + (blockSize.x / 2);
  float yCurr = gameObject.y() + (blockSize.y / 2);

  int xCurrOnGrid = round(yCurr) / blockSize.x; 
  int yCurrOnGrid = round(xCurr) / blockSize.y;

  std::vector<Vector2D<int>> possibleDirectionsVectors;

  // Cue Path planning.
  if ((prevGridPositions.size() == 0) 
      || (((nextGridPosition.y * blockSize.x) + (blockSize.x / 2) - epsilon <= xCurr && xCurr <= (nextGridPosition.y * blockSize.x) + (blockSize.x / 2) + epsilon) 
          && 
          ((nextGridPosition.x * blockSize.y) + (blockSize.y / 2) - epsilon <= yCurr && yCurr <= (nextGridPosition.x * blockSize.y) + (blockSize.y / 2) + epsilon)))
  {
    if (InBounds(xCurrOnGrid,yCurrOnGrid + 1)
      && !(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>(xCurrOnGrid, (yCurrOnGrid + 1))) != prevGridPositions.end())
      && pathGrid[xCurrOnGrid][yCurrOnGrid + 1])
    {
      // North
      possibleDirectionsVectors.push_back(Vector2D<int>(xCurrOnGrid, yCurrOnGrid + 1));
    } 
    
    if (InBounds(xCurrOnGrid,yCurrOnGrid - 1) 
      && !(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>(xCurrOnGrid, (yCurrOnGrid - 1))) != prevGridPositions.end())
      && pathGrid[xCurrOnGrid][yCurrOnGrid - 1]) {
      // South
      possibleDirectionsVectors.push_back(Vector2D<int>(xCurrOnGrid, yCurrOnGrid - 1));
    } 
    
    if (InBounds(xCurrOnGrid + 1,yCurrOnGrid) 
      && !(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>((xCurrOnGrid + 1), yCurrOnGrid)) != prevGridPositions.end())
      && pathGrid[xCurrOnGrid + 1][yCurrOnGrid]) {
      // East
      possibleDirectionsVectors.push_back(Vector2D<int>(xCurrOnGrid + 1, yCurrOnGrid));
    } 
    
    if (InBounds(xCurrOnGrid - 1,yCurrOnGrid) 
      && !(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>((xCurrOnGrid - 1), yCurrOnGrid)) != prevGridPositions.end())
      && pathGrid[xCurrOnGrid - 1][yCurrOnGrid]) {
      // West
      possibleDirectionsVectors.push_back(Vector2D<int>(xCurrOnGrid - 1, yCurrOnGrid));
    }
  }

  if ((possibleDirectionsVectors.size()) > 0)
  {
    std::cout << "Size vector:" << std::to_string(possibleDirectionsVectors.size()) << "\n";
    int dir = rand() % possibleDirectionsVectors.size() + 1;
    std::cout << "Dir:" << std::to_string(dir) << "\n";

    nextGridPosition.x = possibleDirectionsVectors[dir - 1].x;
    nextGridPosition.y = possibleDirectionsVectors[dir - 1].y;
  }
  
  int x2F = (nextGridPosition.y * blockSize.x) + (blockSize.x / 2);
  int y2F = (nextGridPosition.x * blockSize.y) + (blockSize.y / 2);

  float deltaX = x2F - xCurr;
  float deltaY = y2F - yCurr;
  pc->setVx(speed * (deltaX / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));
  pc->setVy(speed * (deltaY / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));

  if (!(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>((xCurrOnGrid), yCurrOnGrid)) != prevGridPositions.end()))
  {
    prevGridPositions.push_back(Vector2D<int>(xCurrOnGrid, yCurrOnGrid));
  }
}

bool RandomWalkComponent::GetDirection() {
  GameObject & gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  return pc->vx() > 0;
}

bool RandomWalkComponent::InBounds(int x, int y) {
  return (x >= 0 && x < pathGrid.size()) 
    &&
    (y >= 0 && y < pathGrid[0].size());
}