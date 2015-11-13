
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Input.hpp"

using namespace ci;
using namespace ci::app;

class SnakeApp : public AppNative {
public:
  void setup();
  void mouseDown(MouseEvent event);
  void keyDown(KeyEvent event);
  void update();
  void draw();
};

void SnakeApp::setup() {
  Input::get();
}

void SnakeApp::mouseDown(MouseEvent event) {}

void SnakeApp::keyDown(KeyEvent event) {
  Input::get().setKeyPush(event.getChar());
}

void SnakeApp::update() {}

void SnakeApp::draw() {
	gl::clear(Color(0, 0, 0));
  Input::get().reset();
}

CINDER_APP_NATIVE( SnakeApp, RendererGl )
