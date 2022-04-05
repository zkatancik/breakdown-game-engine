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


 private:
  Language language_{Language::ENGLISH};

};

#endif