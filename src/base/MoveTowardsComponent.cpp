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
  float xCurr = gameObject.x();
  float yCurr = gameObject.y();

  // TdLevelItem::PATHBLOCK
  std::cout << "Path Grid -> Move Towards Grid:\n";
  for (size_t i = 0; i < pathGrid.size(); i++)
  {
    for (size_t j = 0; j < pathGrid[0].size(); j++)
    {
        std::cout << std::to_string(pathGrid[i][j]) << " ";
    }
    std::cout << "\n";
  }
  
  std::cout << "xyCurr:(" << std::to_string(xCurr) 
    << ","
    << std::to_string(yCurr)
    << ")" << "\n";

  int xCurrOnGrid = round(yCurr) / 64; 
  int yCurrOnGrid = round(xCurr) / 64;

  std::cout << "xyCurrOnGrid:(" << std::to_string(xCurrOnGrid) 
    << ","
    << std::to_string(yCurrOnGrid)
    << ")" << "\n";

  //float x2 = Xs.at(currIter != Xs.size() - 1 ? currIter + 1 : 0);
  //float y2 = Ys.at(currIter != Ys.size() - 1 ? currIter + 1 : 0);
  int x2;
  int y2;

  // Cue Path planning.
  if ((prevGridPositions.size() == 0) 
      || ((nextGridPosition.y * 64 - 1.5 < xCurr < nextGridPosition.y * 64 + 1.5) 
          && 
          (nextGridPosition.x * 64 - 1.5 < yCurr < nextGridPosition.x * 64 + 1.5)))
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
  std::cout << "To go xyCurrOnGrid:(" << std::to_string(nextGridPosition.x) 
    << ","
    << std::to_string(nextGridPosition.y)
    << ")" << "\n";

  int x2F = nextGridPosition.y * 64;
  int y2F = nextGridPosition.x * 64;

  std::cout << "To go xyCurr:(" << std::to_string(x2F) 
    << ","
    << std::to_string(y2F)
    << ")" << "\n";

  float deltaX = x2F - xCurr;
  float deltaY = y2F - yCurr;
  pc->setVx(speed * (deltaX / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));
  pc->setVy(speed * (deltaY / (std::sqrt(deltaX * deltaX + deltaY * deltaY))));

  // std::cout << "Bef prev:(" << std::to_string(prevGridPosition.x) 
  //   << ","
  //   << std::to_string(prevGridPosition.y)
  //   << ")" << "\n";

  if (!(std::find(prevGridPositions.begin(), prevGridPositions.end(), Vector2D<int>((xCurrOnGrid), yCurrOnGrid)) != prevGridPositions.end()))
  {
    prevGridPositions.push_back(Vector2D<int>(xCurrOnGrid, yCurrOnGrid));
  }
  
  // std::cout << "After prev:(" << std::to_string(prevGridPosition.x) 
  //   << ","
  //   << std::to_string(prevGridPosition.y)
  //   << ")" << "\n";

  // if (std::abs(xCurr - x2) < speed / 60. && std::abs(yCurr - y2) < speed / 60.) {
  //   currIter = currIter != Xs.size() - 1 ? currIter + 1 : 0;
  // }
}

bool MoveTowardsComponent::GetDirection() {
  GameObject & gameObject = getGameObject();
  std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
  return pc->vx() > 0;
  //return true;
}

bool MoveTowardsComponent::InBounds(int x, int y) {
  return (x >= 0 && x < pathGrid.size()) 
    &&
    (y >= 0 && y < pathGrid[0].size());
}