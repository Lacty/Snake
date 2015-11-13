
#include "Player.hpp"
#include "cinder/gl/gl.h"


Player::Player() :
cell_size(Width / Row, Height / Column),
head_dir(Down),
size(cell_size),
offset(size / 2)
{
  bodies.emplace_back(Body(ci::Vec2i(0, 10), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 9), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 8), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 7), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 6), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 5), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 4), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 3), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 2), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 1), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 0), head_dir));
}

Player::Body::Body(const ci::Vec2i& pos,
                   const Direction& dir) :
pos(pos),
dir(dir) {}


void Player::advanceInDirection(ci::Vec2i& pos, Direction dir) {
  switch (dir) {
    case Up: {
      pos += ci::Vec2i(0, -1);
    } break;
    
    case Down: {
      pos += ci::Vec2i(0, 1);
    } break;
    
    case Right: {
      pos += ci::Vec2i(1, 0);
    } break;
    
    case Left: {
      pos += ci::Vec2i(-1, 0);
    } break;
  }
}

void Player::swapDirection(Direction &dir1, Direction &dir2) {
  static Direction d = dir2;
  dir2 = dir1;
  dir1 = d;
}

void Player::setHeadDirection(const Direction &dir) {
  head_dir = dir;
}

const Direction& Player::getHeadDirection() const {
  return head_dir;
}

void Player::update() {
  static Direction current_dir;
  static Direction next_dir;
  
  for (auto itr = bodies.begin(); itr != bodies.end(); itr++) {
    if (itr == bodies.begin()) {
      current_dir = itr->dir;
      itr->dir = head_dir;
      advanceInDirection(itr->pos, itr->dir);
    }
    else {
      swapDirection(current_dir, next_dir);
      current_dir = itr->dir;
      itr->dir = next_dir;
      advanceInDirection(itr->pos, itr->dir);
    }
  }
}

void Player::draw() {
  using namespace ci;
  gl::color(1.f, 0.6f, 0.f);
  for (auto& body : bodies) {
    gl::drawCube(Vec3i(body.pos * cell_size + offset, 0), Vec3i(size, 0));
  }
}