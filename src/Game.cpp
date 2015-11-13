
#include "Game.hpp"
#include "Input.hpp"


Game::Game(int fps) :
fps(fps) {}


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
  updateHeadDirection();
  static int Fps = 0;
  Fps++;
  if (Fps > fps) {
    player.update();
    Fps = 0;
  }
}

void Game::draw() {
  player.draw();
}