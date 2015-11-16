
#include "Player.hpp"
#include "cinder/gl/gl.h"


Player::Player() :
cell_size(Width / Row, Height / Column),
head_dir(Down),
size(cell_size),
offset(size / 2),
is_eatMyBody(false)
{
  bodies.emplace_back(Body(ci::Vec2i(0, 5), head_dir));
  bodies.emplace_back(Body(ci::Vec2i(0, 4), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 3), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 2), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 1), Down));
  bodies.emplace_back(Body(ci::Vec2i(0, 0), Down));
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
  Direction d;
  d = dir1;
  dir1 = dir2;
  dir2 = d;
}

void Player::swapPosition(ci::Vec2i &pos1, ci::Vec2i &pos2) {
  ci::Vec2i pos;
  pos = pos1;
  pos1 = pos2;
  pos2 = pos;
}

void Player::warp() {
  auto body_itr = bodies.begin();
  if (body_itr->pos.x < 0) {
    body_itr->pos.x = Row - 1;
  }
  else if (body_itr->pos.x >= Row) {
    body_itr->pos.x = 0;
  }
  
  if (body_itr->pos.y < 0) {
    body_itr->pos.y = Column - 1;
  }
  else if (body_itr->pos.y >= Column) {
    body_itr->pos.y = 0;
  }
}


void Player::setHeadDirection(const Direction &dir) {
  head_dir = dir;
}

const bool Player::isConfiguredDirection() const {
  auto body_itr = bodies.begin();
  return head_dir != body_itr->dir;
}

const Direction& Player::getHeadDirection() const {
  return head_dir;
}

const ci::Vec2i& Player::getHeadPosition() const {
  auto body_itr = bodies.begin();
  return body_itr->pos;
}

const bool Player::isEatMyBody() const {
  return is_eatMyBody;
}

void Player::eat() {
  auto body_itr = bodies.end();
  auto last = (--body_itr);
  
  bodies.emplace_back(Body(last->pos, last->dir));
  bodies.emplace_back(Body(last->pos, last->dir));
  bodies.emplace_back(Body(last->pos, last->dir));
}

void Player::update(Map& map) {
  ci::Vec2i current_pos;
  ci::Vec2i next_pos;
  
  for (auto itr = bodies.begin(); itr != bodies.end(); itr++) {
    if (itr == bodies.begin()) {
      current_pos = itr->pos;
      itr->dir = head_dir;
      advanceInDirection(itr->pos, itr->dir);
      warp();
    }
    else {
      swapPosition(current_pos, next_pos);
      current_pos = itr->pos;
      itr->pos = next_pos;
    }
  }
  
  for (int r = 0; r < Row; r++) {
    for (int c = 0; c < Column; c++) {
      map.m[r][c] = 0;
    }
  }
  
  for (auto body : bodies) {
    map.m[body.pos.x][body.pos.y] = 1;
  }
  
  for (auto itr = bodies.begin(); itr != bodies.end(); itr++) {
    if (itr != bodies.begin()) {
      if (itr->pos == getHeadPosition()) {
        is_eatMyBody = true;
      }
    }
  }
}

void Player::draw() {
  using namespace ci;
  gl::color(1.f, 0.6f, 0.f);
  for (auto& body : bodies) {
    gl::drawCube(Vec3i(body.pos * cell_size + offset, 0), Vec3f(size * 0.9f, 0));
  }
}