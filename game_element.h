#include <iostream>

#include "cpputils/graphics/image.h"

#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 private:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_ = true;

 public:
  GameElement();
  GameElement(int x, int y, int w, int h);
  int GetX();
  void SetX(int x);
  int GetY();
  void SetY(int y);
  int GetWidth();
  int GetHeight();
  bool GetIsActive();
  void SetIsActive(bool is_active);
  virtual void Draw(graphics::Image& screen) = 0;
  virtual void Move(const graphics::Image& element) = 0;
  bool IntersectsWith(GameElement* element);
  bool IsOutOfBounds(const graphics::Image& image);
};
#endif
