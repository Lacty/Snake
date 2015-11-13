
#include "Input.hpp"


Input& Input::get() {
  static Input instance;
  return instance;
}

void Input::reset() {
  key.clear();
}

void Input::setKeyPush(int key_number) {
  key.emplace(key_number);
}

bool Input::isPush(int key_number) {
  if (key.find(key_number) == key.end()) return false;
  key.erase(key.find(key_number));
  return true;
}