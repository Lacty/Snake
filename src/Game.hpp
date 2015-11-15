
#pragma once
#include "Player.hpp"


class Game {
private:
  int fps;
  bool isSelectDirection;
  Player player;
  
  void updateHeadDirection();
  
public:
  Game() = default;
  Game(int fps);
  
  void update();
  void draw();
};
