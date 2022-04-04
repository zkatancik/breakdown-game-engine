#ifndef TEXT_OBJECT_HPP
#define TEXT_OBJECT_HPP
#include "base/GameObject.hpp"
#include "TextureRenderComponent.hpp"
#include <string>

class TextObject : public GameObject {
 public:
  TextObject(Level& level, float x, float y, int fontSize, const std::string& text, Language language);

  void changeLanguage(Language language);

 private:
  std::string mEnglishText;
  int mFontSize{32};
  const std::string mButtonFont = "Gageda.ttf";
  std::shared_ptr<TextureRenderComponent> mRenderer;
};
#endif
