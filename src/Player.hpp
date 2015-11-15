
#pragma once
#include <vector>
#include "WindowSize.hpp"
#include "CellSize.hpp"
#include "cinder/Vector.h"


enum Direction {
  Up,
  Down,
  Right,
  Left
};

class Player {
private:
  ci::Vec2i cell_size;
  
  Direction head_dir;
  
  ci::Vec2i size;
  ci::Vec2i offset;
  
  struct Body {
    ci::Vec2i pos;
    Direction dir;
    Body(const ci::Vec2i& pos,
         const Direction& dir);
  };
  std::vector<Body> bodies;
  
  void advanceInDirection(ci::Vec2i& pos, Direction dir);
  void swapDirection(Direction& dir1, Direction& dir2);
  void swapPosition(ci::Vec2i& pos1, ci::Vec2i& pos2);
  
public:
  Player();
  
  void setHeadDirection(const Direction& dir);
  const bool isConfiguredDirection() const;
  const Direction& getHeadDirection() const;
  
  void update();
  void draw();
};
