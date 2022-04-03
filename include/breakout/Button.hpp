#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>
#include <base/GameObject.hpp>
#include "base/ResourceManager.hpp"
#include "base/TextObject.hpp"
#include "base/Level.hpp"
#include "base/SelectableComponent.hpp"

/**
 * @brief A class representing a clickable UI Text Button.
 */
class Button : public GameObject {
 private:
  std::shared_ptr<TextObject> mText;

 public:
  Button(Level& level, float x, float y, float w, float h, const std::string& text,
         const std::function<void(void)>& selectHook);
};

#endif