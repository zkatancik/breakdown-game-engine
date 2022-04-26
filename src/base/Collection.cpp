#include "base/Collection.hpp"
#include <algorithm>

Collection::Collection(Level &level) : mLevel(level) {}

void Collection::addGameObject(const std::shared_ptr<GameObject>& gameObject) {
  mLevel.addObject(gameObject);
  mObjects.push_back(gameObject->weak_from_this());
}
void Collection::removeGameObject(const std::shared_ptr<GameObject>& gameObject) {
  mLevel.removeObject(gameObject);
  for (auto it = mObjects.begin(); it != mObjects.end(); it++) {
    if (it->lock() == gameObject) {
      mObjects.erase(it);
      break;
    }
  }
}
const std::vector<std::weak_ptr<GameObject>> &Collection::GetObjects() const {
  return mObjects;
}
