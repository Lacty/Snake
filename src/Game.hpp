
#pragma once
#include "Player.hpp"


class Game {
private:
  Player player;
  
public:
  Game();
  
  void update();
  void draw();
};
