
#include "Player.hpp"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"


Player::Player() :
cell_size(Width / Row, Height / Column),
head_dir(Down),
size(cell_size),
offset(size / 2),
is_eatMyBody(false)
{
  bodies.emplace_back(Body(ci::Vec2i(0, 5), head_dir, 1.0f, ci::ColorA(1.0f, 0.6f, 0.0f, 1.0f)));
  bodies.emplace_back(Body(ci::Vec2i(0, 4), Down,     1.0f, ci::ColorA(1.0f, 0.6f, 0.0f, 1.0f)));
  bodies.emplace_back(Body(ci::Vec2i(0, 3), Down,     1.0f, ci::ColorA(1.0f, 0.6f, 0.0f, 1.0f)));
  bodies.emplace_back(Body(ci::Vec2i(0, 2), Down,     1.0f, ci::ColorA(1.0f, 0.6f, 0.0f, 1.0f)));
  bodies.emplace_back(Body(ci::Vec2i(0, 1), Down,     1.0f, ci::ColorA(1.0f, 0.6f, 0.0f, 1.0f)));
  bodies.emplace_back(Body(ci::Vec2i(0, 0), Down,     1.0f, ci::ColorA(1.0f, 0.6f, 0.0f, 1.0f)));
}

Player::Body::Body(const ci::Vec2i& pos,
                   const Direction& dir,
                   const float alpha,
                   const ci::ColorA& color) :
pos(pos),
dir(dir),
alpha(alpha),
color(color) {}


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

void Player::dead() {
  std::cout << "dead" <<std::endl;
  ci::Anim<ci::Vec2i> end;
  for (auto& body : bodies) {
    body.anim = body.pos;
    std::cout << "body.pos = " << body.pos << std::endl;
    end = ci::Vec2i(ci::randInt(0, Row), ci::randInt(0, Column));
    ci::app::timeline().apply(&body.anim, end.value(),
                              0.6f, ci::easeInOutCirc);
  }
}

void Player::deadUpdate() {
  for (auto& body : bodies) {
    if (body.alpha <= 0) return;
    body.pos = body.anim;
    std::cout << "body.anim = " << body.anim << std::endl;
    std::cout << "body.pos = " << body.pos << std::endl;
    body.alpha -= 0.018f;
  }
}

void Player::eat() {
  auto body_itr = bodies.end();
  auto last = (--body_itr);
  
  bodies.emplace_back(Body(last->pos, last->dir, 1.0f, ci::ColorA(1.0f, 0.6f, 0.0f, 1.0f)));
  bodies.emplace_back(Body(last->pos, last->dir, 1.0f, ci::ColorA(1.0f, 0.6f, 0.0f, 1.0f)));
  bodies.emplace_back(Body(last->pos, last->dir, 1.0f, ci::ColorA(1.0f, 0.6f, 0.0f, 1.0f)));
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
  gl::enableAlphaBlending();
  
  for (auto body : bodies) {
    gl::color(ColorA(body.color.r, body.color.g, body.color.b, body.alpha));
    gl::drawCube(Vec3i(body.pos * cell_size + offset, 0), Vec3f(size * 0.9f, 0));
  }
  
  gl::disableAlphaBlending();
}