#include "base/Level.hpp"
#include "base/PhysicsManager.hpp"
#include <algorithm>

Level::Level(int w, int h):
mW(w),
mH(h)
{
}

Level::~Level()
{
}

void
Level::finalize()
{
  mObjects.clear();
  mObjectsToAdd.clear();
  mObjectsToRemove.clear();
}

void
Level::addObject(std::shared_ptr<GameObject> object)
{
  mObjectsToAdd.push_back(object);
}

void
Level::removeObject(std::shared_ptr<GameObject> object)
{
  mObjectsToRemove.push_back(object);
}

bool Level::FindObject(const std::shared_ptr<GameObject>& obj) {
  return obj != nullptr && std::find(mObjects.begin(), mObjects.end(), obj) != mObjects.end();
}

void
Level::update()
{
  for (auto obj: mObjectsToAdd) {
    mObjects.push_back(obj);
  }
  mObjectsToAdd.clear();

  for (auto gameObject: mObjects) {
    gameObject->update();
  }

  PhysicsManager::getInstance().step();
  for (auto gameObject: mObjects) {
    gameObject->postStep();
  }

  for (auto obj: mObjectsToRemove) {
    auto elem = std::find(mObjects.begin(), mObjects.end(), obj);
    if (elem != mObjects.end()) {
      mObjects.erase(elem);
    }
  }
  mObjectsToRemove.clear();
}

void
Level::render(SDL_Renderer * renderer)
{
  for (auto gameObject: mObjects) {
    gameObject->render(renderer);
  }
}
