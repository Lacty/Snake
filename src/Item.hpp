
#pragma once
#include "cinder/Vector.h"
#include "Map.hpp"


class Item {
private:
  ci::Vec2i pos;
  ci::Vec2i size;
  ci::Vec2i offset;
  bool is_eaten;
  
public:
  Item();
  
  void spawn(Map& map);
  
  void draw();
  
  const ci::Vec2i& getPos() const;
  const bool isEaten() const;
  void setState(bool state);
};