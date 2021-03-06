#ifndef BASE_LEVEL
#define BASE_LEVEL

#include "base/GameObject.hpp"
#include <SDL.h>
#include <memory>
#include <vector>
#include "base/ResourceManager.hpp"
#include "base/TextComponent.hpp"

//! \brief A level in the game.  Essentially mannages a collection of game
//! objects, and does some collision detection.
 class Level : public std::enable_shared_from_this<Level> {
 public:

  Level(int w, int h);
  virtual ~Level();

  virtual void initialize() {};
  void finalize();

  inline int w() const { return mW; }
  inline int h() const { return mH; }

  void addObject(std::shared_ptr<GameObject> object); //!< Set an object to be added.
  void removeObject(std::shared_ptr<GameObject> object); //!< Set an object to be removed.
  bool FindObject(const std::shared_ptr<GameObject> &obj); //!< Finds an object.

  void update(); //!< Update the objects in the level.
  void render(SDL_Renderer * renderer); //!< Render the level.

  void changeLanguage(Language language); //!< Change the language of all Game objects with Text Components

  const std::vector<std::shared_ptr<GameObject>> &getGameObjects() const;
  const std::vector<std::shared_ptr<GameObject>> &getGameObjectsToAdd() const;
  const std::vector<std::shared_ptr<GameObject>> &getGameObjectsToRemove() const;

 private:

  Level(const Level &) = delete;
  void operator=(Level const&) = delete;

  int mW, mH;
  std::vector<std::shared_ptr<GameObject>> mObjects{};

  std::vector<std::shared_ptr<GameObject>> mObjectsToAdd{};

  private:
   std::vector<std::shared_ptr<GameObject>> mObjectsToRemove{};

};

#endif
