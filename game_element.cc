#include "game_element.h"

int GameElement::GetX() { return x_; }
void GameElement::SetX(int x) { x_ = x; }
int GameElement::GetY() { return y_; }
void GameElement::SetY(int y) { y_ = y; }
int GameElement::GetWidth() { return width_; }
int GameElement::GetHeight() { return height_; }
GameElement::GameElement(int x, int y, int w, int h) {
  x_ = x;
  y_ = y;
  width_ = w;
  height_ = h;
}
GameElement::GameElement() {
  x_ = 0;
  y_ = 0;
  width_ = 50;
  height_ = 50;
}
bool GameElement::GetIsActive() { return is_active_; }
void GameElement::SetIsActive(bool is_active) { is_active_ = is_active; }
void GameElement::Draw(graphics::Image& screen) {
  // a 5x5 black rectangle at the game element's current x and y position
  screen.DrawRectangle(x_, y_, 5, 5, 0, 0, 0);
}

bool GameElement::IntersectsWith(GameElement* element) {
  if (element->GetX() + element->GetWidth() < GetX()) {
    return false;
  } else if (GetX() + GetWidth() < element->GetX()) {
    return false;
  } else if (element->GetY() + element->GetHeight() < GetY()) {
    return false;
  } else if (GetY() + GetHeight() < element->GetY()) {
    return false;
  } else {
    return true;
  }
}

bool GameElement::IsOutOfBounds(const graphics::Image& image) {
  if (GetY() + GetHeight() > image.GetHeight() ||
      GetX() + GetWidth() > image.GetWidth() || GetY() < 0 || GetX() < 0) {
    return true;
  } else {
    return false;
  }
}
