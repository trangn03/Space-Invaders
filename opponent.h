#include <memory>

#include "cpputils/graphics/image.h"
#include "game_element.h"

#ifndef OPPONENT_H
#define OPPONENT_H

class Opponent : public GameElement {
 private:
  int count = 0;

 public:
  Opponent();
  Opponent(int x, int y);
  void Draw(graphics::Image& screen);
  void Move(const graphics::Image& opponent);
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile();
  OpponentProjectile(int x, int y);
  void Draw(graphics::Image& screen);
  void Move(const graphics::Image& o_projectile);
};
#endif
