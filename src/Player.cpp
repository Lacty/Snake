
#include "Player.hpp"
#include "cinder/gl/gl.h"


Player::Player() :
cell_size(Width / Row, Height / Column),
head_dir(Down),
size(cell_size),
offset(size / 2)
{
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

void Player::update() {
  static Direction current_dir;
  static Direction next_dir;
  
  for (auto itr = bodies.begin(); itr != bodies.end(); ++itr) {
    if (itr == bodies.begin()) {
      next_dir = itr->dir;
      
      itr->dir = head_dir;
    }
    else {
      current_dir = itr->dir;
      
      itr->dir = next_dir;
    }
    
    advanceInDirection(itr->pos, itr->dir);
  }
}

void Player::draw() {
  using namespace ci;
  gl::color(1.f, 0.6f, 0.f);
  for (auto& body : bodies) {
    gl::drawCube(Vec3i(body.pos * cell_size + offset, 0), Vec3i(size, 0));
  }
}