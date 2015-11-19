
#include "Score.hpp"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <sstream>


Score::Score(int initScore) :
mScore(initScore)
{
  pos = ci::Vec2i(0, 60);
  font = ci::Font(ci::app::loadAsset("player1up.ttf"), 30);
}


void Score::addScore() {
  mScore++;
}

void Score::draw() {
  std::ostringstream otr;
  otr << "Eat : " << mScore;
  ci::gl::pushModelView();
  ci::gl::enableAlphaBlending();
  ci::gl::translate(pos);
  ci::gl::drawStringCentered(otr.str(), ci::app::getWindowCenter(), ci::Color(1, 1, 1), font);
  ci::gl::disableAlphaBlending();
  ci::gl::popModelView();
}