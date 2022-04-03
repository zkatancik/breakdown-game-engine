#ifndef BASE_GAME_OBJECT
#define BASE_GAME_OBJECT

#include "base/GenericComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/RenderComponent.hpp"
#include <SDL.h>
#include <memory>
#include <vector>

class Level;

/**
 * @brief Represents an object in the game.  Has some essential
 * properties (position and size), a tag (identifying the general
 * category of object), and a collection of components, including any
 * number of generic components and optionally a physics component
 * and a render component.
 * 
 * We originally implemented our game as fully object-centric. But after seeing
 * Lab 6 and its potential for code reuse and clarity, we switched to a more
 * property centric approach with "Components". This gave flexibility (for example
 * for implementing the enemy class, we could reuse various components from Jack).
 * Another driving factor was because we think this will make implementing the
 * Level Editor for the next milestone easier. For example, rendering blocks as
 * grid objects is a small change now (via GridRenderComponent).
 */
class GameObject: public std::enable_shared_from_this<GameObject> {
 public:

  explicit GameObject(Level & level);
  GameObject(Level & level, float x, float y, float w, float h, int tag);
  virtual ~GameObject();

  void startUp(float x, float y, float w, float h, int tag);

  inline int tag() const { return mTag; }

  inline void setX(float x) { mX = x; }
  inline void setY(float y) { mY = y; }

  inline void setW(float w) {mW = w;}
  inline void setH(float h) {mH = h;}

  inline float x() const { return mX; }
  inline float y() const { return mY; }
  inline float w() const { return mW; }
  inline float h() const { return mH; }

  inline void addGenericComponent(std::shared_ptr<GenericComponent> comp) { mGenericComponents.push_back(comp); }
  inline void setPhysicsComponent(std::shared_ptr<PhysicsComponent> comp) { mPhysicsComponent = comp; }
  inline void setRenderComponent(std::shared_ptr<RenderComponent> comp) { mRenderComponent = comp; }

  inline std::vector<std::shared_ptr<GenericComponent>> genericComponents() { return mGenericComponents; }
  inline std::shared_ptr<PhysicsComponent> physicsComponent() { return mPhysicsComponent; }
  inline std::shared_ptr<RenderComponent> renderComponent() { return mRenderComponent; }

  virtual void update(); //!< Update the object.
  void collision(std::shared_ptr<GameObject> obj); //!< Handle collisions with another object.
  void postStep(); //!< After the physics step for the object.
  void render(SDL_Renderer * renderer); //!< Render the object.

  bool isOverlapping(const GameObject & obj) const; //!< Determine if this object is overlapping with another.
  bool isOverlapping(float px, float py) const; //!< Determine if this object is overlapping with a point.

 private:

  GameObject(const GameObject &) = delete;
  void operator=(GameObject const&) = delete;

  Level & mLevel;

  float mX, mY, mW, mH;
  int mTag;

  std::vector<std::shared_ptr<GenericComponent>> mGenericComponents;
  std::shared_ptr<PhysicsComponent> mPhysicsComponent;
  std::shared_ptr<RenderComponent> mRenderComponent;

};
#endif
