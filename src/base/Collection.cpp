#include "base/Collection.hpp"
#include <algorithm>

Collection::Collection(Level &level) : mLevel(level) {}

void Collection::addGameObject(std::shared_ptr<GameObject> gameObject) {
  mLevel.addObject(gameObject);
  mObjects.push_back(gameObject->weak_from_this());
}
void Collection::removeGameObject(std::shared_ptr<GameObject> gameObject) {
  mLevel.removeObject(gameObject);
  auto it =  std::find(mObjects.begin(), mObjects.end(), gameObject->weak_from_this());
  if (it != mObjects.end())
    mObjects.erase(it);
}
const std::vector<std::weak_ptr<GameObject>> &Collection::GetObjects() const {
  return mObjects;
}
