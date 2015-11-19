
#include "Game.hpp"
#include "Input.hpp"


Game::Game(int fps) :
fps(fps),
score(0),
isGameOver(false)
{
  font = ci::Font(ci::app::loadAsset("player1up.ttf"), 50);
}


void Game::updateHeadDirection() {
  if (Input::get().isPush('w') && (player.getHeadDirection() != Down)) {
    player.setHeadDirection(Up);
  }
  else if (Input::get().isPush('a') && (player.getHeadDirection() != Right)) {
    player.setHeadDirection(Left);
  }
  else if (Input::get().isPush('s') && (player.getHeadDirection() != Up)) {
    player.setHeadDirection(Down);
  }
  else if (Input::get().isPush('d') && (player.getHeadDirection() != Left)) {
    player.setHeadDirection(Right);
  }
}

void Game::update() {
  if (item.isEaten()) {
    item.spawn(map);
  }
  
  if (!player.isConfiguredDirection()) {
    updateHeadDirection();
  }
  
  if (isGameOver) {
    player.deadUpdate();
    if (Input::get().isPush('r')) {
      item = Item();
      player = Player();
      isGameOver = false;
    }
  }
  
  if (isGameOver) return;
  
  if (player.isEatMyBody()) {
    player.dead();
    isGameOver = true;
  }
  
  static int Fps = 0;
  Fps++;
  if (Fps > fps) {
    player.update(map);
    if (player.getHeadPosition() == item.getPos()) {
      score.addScore();
      player.eat();
      item.setState(true);
    }
    Fps = 0;
  }
}

void Game::draw() {
  player.draw();
  item.draw();
  
  if (!isGameOver) return;
  ci::Vec2i pos = ci::Vec2i(ci::app::getWindowCenter().x, 200);
  ci::gl::pushModelView();
  ci::gl::enableAlphaBlending();
  ci::gl::translate(pos);
  ci::gl::drawStringCentered("~Game Over~", ci::Vec2i::zero(), ci::Color(1, 1, 1), font);
  ci::gl::disableAlphaBlending();
  ci::gl::popModelView();
  score.draw();
}