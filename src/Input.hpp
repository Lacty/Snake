
#pragma once
#include <set>


class Input {
private:
  std::set<int> key;
  
  Input() = default;
  
public:
  static Input& get();
  
  void reset();
  
  void setKeyPush(int key_number);
  
  bool isPush(int key);
};
