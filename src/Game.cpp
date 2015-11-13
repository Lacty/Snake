
#include "Game.hpp"


Game::Game() {}


void Game::update() {
  player.update();
}

void Game::draw() {
  player.draw();
}