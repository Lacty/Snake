
#pragma once
#include "Player.hpp"
#include "Item.hpp"
#include "cinder/app/AppNative.h"
#include "cinder/Font.h"
#include "Map.hpp"


class Game {
private:
  int fps;
  Player player;
  Item item;
  
  bool isGameOver;
  ci::Font font;
  
  Map map;
  
  void updateHeadDirection();
  
public:
  Game() = default;
  Game(int fps);
  
  void update();
  void draw();
};
