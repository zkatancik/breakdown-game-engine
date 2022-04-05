#ifndef BREAKOUT_LEVEL_HPP
#define BREAKOUT_LEVEL_HPP

#include <base/Level.hpp>
#include "base/ResourceManager.hpp"
#include "breakout/Tag.hpp"
class BreakoutLevel : public Level {
 public:

  void initialize() override {};

  BreakoutLevel(int w, int h, Language language) : Level(w, h),
  language_(language) {};

  void changeLanguage(Language language) {
    for (auto gameObject : Level::GetGameObjects()) {
      if (gameObject->tag() == TextTag) {
      }
    }
  }

 private:
  Language language_{Language::ENGLISH};

};

#endif