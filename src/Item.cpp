
#include "Item.hpp"
#include "CellSize.hpp"
#include "WindowSize.hpp"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"


Item::Item() :
is_eaten(false),
size(Width / Row, Height / Column),
offset(size / 2) {}

void Item::spawn(Map& map) {
  while (is_eaten) {
    pos = ci::Vec2i(ci::randInt(0, Row - 1), ci::randInt(0, Column - 1));
    if (!map.m[pos.x][pos.y]) {
      is_eaten = false;
    }
  }
}

void Item::draw() {
  if (isEaten()) return;
  ci::gl::color(1, 1, 1);
  ci::gl::drawCube(ci::Vec3f(pos * size + offset, 0), ci::Vec3f(size * 0.9f, 0));
}

const ci::Vec2i& Item::getPos() const {
  return pos;
}

const bool Item::isEaten() const {
  return is_eaten;
}

void Item::setState(bool state) {
  is_eaten = state;
}