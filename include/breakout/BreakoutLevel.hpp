#ifndef BREAKOUT_LEVEL_HPP
#define BREAKOUT_LEVEL_HPP

#include <base/Level.hpp>
#include "base/ResourceManager.hpp"
#include "breakout/Tag.hpp"
class BreakoutLevel : public Level {
 public:

  void initialize() override {};

  BreakoutLevel(int w, int h) : Level(w, h) {};

};

#endif