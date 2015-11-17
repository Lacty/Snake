
#include "Game.hpp"
#include "Input.hpp"


Game::Game(int fps) :
fps(fps),
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
  ci::gl::enableAlphaBlending();
  ci::gl::drawStringCentered("~Game Over~", ci::app::getWindowCenter(), ci::Color(1, 1, 1), font);
  ci::gl::disableAlphaBlending();
}