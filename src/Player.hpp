
#pragma once
#include <vector>
#include "WindowSize.hpp"
#include "CellSize.hpp"
#include "cinder/Vector.h"
#include "Map.hpp"


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
  
  bool is_eatMyBody;
  
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
  
  void warp();
  
public:
  Player();
  
  void setHeadDirection(const Direction& dir);
  const bool isConfiguredDirection() const;
  const Direction& getHeadDirection() const;
  const ci::Vec2i& getHeadPosition() const;
  
  const bool isEatMyBody() const;
  
  void eat();
  
  void update(Map& map);
  void draw();
};
