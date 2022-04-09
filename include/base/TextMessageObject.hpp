#ifndef TEXT_MESSAGE_OBJECT_HPP
#define TEXT_MESSAGE_OBJECT_HPP
#include <base/GameObject.hpp>
#include <functional>
#include "base/Tag.hpp"

#include "base/Level.hpp"
#include "base/ResourceManager.hpp"
#include "base/SelectableComponent.hpp"
#include "base/TextComponent.hpp"
#include "base/TextureRenderComponent.hpp"

/**
 * @brief A Game object that only contains
 */
class TextMessageObject : public GameObject {
 public:

  TextMessageObject(Level& level,
                    const std::string& message,
                    float x, float y,
                    const std::string& fontFile,
                    int fontSize = 64);
};

#endif