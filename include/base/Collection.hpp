#ifndef BASE_COLLECTION_HPP
#define BASE_COLLECTION_HPP
#include "base/Level.hpp"

/**
 * Represents a collection of game objects. Much like a Level, but does not call update on each game object
 */
class Collection {
 public:
  explicit Collection(Level& level);

  void addGameObject(const std::shared_ptr<GameObject>& gameObject);

  void removeGameObject(const std::shared_ptr<GameObject>& gameObject);

  const std::vector<std::weak_ptr<GameObject>> &GetObjects() const;


 private:
  Level& mLevel;
  std::vector<std::weak_ptr<GameObject>> mObjects;
};
#endif