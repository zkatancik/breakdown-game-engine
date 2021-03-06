#include "base/GameObject.hpp"

#include <SDL.h>

GameObject::GameObject(Level& level) : mLevel(level) {}

GameObject::GameObject(Level& level, float x, float y, float w, float h,
                       int tag)
    : mLevel(level), mX(x), mY(y), mW(w), mH(h), mTag(tag) {}

GameObject::~GameObject() {}

void GameObject::update() {
  for (auto genericComponent : mGenericComponents) {
    if (isVisibleOnScreen)
    {
      genericComponent->update(mLevel);
    }
  }
}

void GameObject::collision(std::shared_ptr<GameObject> obj) {
  for (auto genericComponent : mGenericComponents) {
    if (isVisibleOnScreen)
    {
      genericComponent->collision(mLevel, obj);
    }
  }
}

void GameObject::postStep() {
  if (mPhysicsComponent && isVisibleOnScreen) {
    mPhysicsComponent->postStep();
  }
}

void GameObject::render(SDL_Renderer* renderer) {
  if (mRenderComponent && isVisibleOnScreen) {
    mRenderComponent->render(renderer);
  }
}

bool GameObject::isOverlapping(const GameObject& obj) const {
  SDL_Rect thisRect = {int(x()), int(y()), int(w()), int(h())};
  SDL_Rect objRect = {int(obj.x()), int(obj.y()), int(obj.w()), int(obj.h())};
  SDL_Rect outRect;
  return SDL_IntersectRect(&thisRect, &objRect, &outRect);
}

bool GameObject::isOverlapping(float px, float py) const {
  SDL_Rect thisRect = {int(x()), int(y()), int(w()), int(h())};
  SDL_Point point = {int(px), int(py)};
  return SDL_PointInRect(&point, &thisRect);
}