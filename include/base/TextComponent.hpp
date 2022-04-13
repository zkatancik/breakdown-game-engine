#ifndef TEXT_COMPONENT_HPP
#define TEXT_COMPONENT_HPP
#include "base/GenericComponent.hpp"
#include "base/ResourceManager.hpp"
#include "base/TextureRenderComponent.hpp"

/**
 * @brief Adds a text (with translation) field to a game object. Requires a
 * renderer to be able to show its value on screen
 */
class TextComponent : public GenericComponent {
 public:
  TextComponent(GameObject &gameObject, std::string engtext, int fontSize,
                std::string fontPath,
                std::shared_ptr<TextureRenderComponent> renderComponent,
                Language language = ENGLISH,
                std::vector<int> color = {255, 255, 255, 0});

  void update(Level &level) override;

  void changeLanguage(Language language);

  inline const std::string &GetMText() const { return mText; }
  inline void SetMText(const std::string &m_text) { mText = m_text; }

  inline const std::string &GetMFontPath() const { return mFontPath; }
  inline void SetMFontPath(const std::string &m_font_path) {
    mFontPath = m_font_path;
  }
  inline int GetMFontSize() const { return mFontSize; }
  inline void SetMFontSize(int m_font_size) { mFontSize = m_font_size; }

 private:
  std::shared_ptr<TextureRenderComponent> mRenderComponent;
  std::string mText{};
  std::string mFontPath{};
  Language mLanguage;
  int mFontSize{16};
  std::vector<int> mColor;
};

#endif