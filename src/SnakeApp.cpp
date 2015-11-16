
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <memory>

#include "WindowSize.hpp"

#include "Input.hpp"
#include "Game.hpp"

using namespace ci;
using namespace ci::app;

class SnakeApp : public AppNative {
private:
  Game game;
  Vec3f pos;
  
public:
  void setup();
  
  void prepareSettings(Settings* settings) {
    // １秒あたりの画面更新回数制限を禁止する
    settings->disableFrameRate();
  }
  
  void mouseDown(MouseEvent event);
  void keyDown(KeyEvent event);
  void update();
  void draw();
};

void SnakeApp::setup() {
  setWindowSize(Width, Height);
  Input::get();
  
  game = Game(8);
}

void SnakeApp::mouseDown(MouseEvent event) {}

void SnakeApp::keyDown(KeyEvent event) {
  Input::get().setKeyPush(event.getChar());
}

void SnakeApp::update() {
  game.update();
}

void SnakeApp::draw() {
	gl::clear(Color(0.4f, 0.4f, 0.4f));
  
  game.draw();
  
  Input::get().reset();
}

CINDER_APP_NATIVE( SnakeApp, RendererGl )
