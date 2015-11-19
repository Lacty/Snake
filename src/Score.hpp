
#pragma once
#include "cinder/Vector.h"
#include "cinder/Font.h"


class Score {
private:
  int mScore;
  ci::Vec2i pos;
  ci::Font font;
  
public:
  Score() = default;
  Score(int initScore);
  
  void addScore();
  void draw();
};
