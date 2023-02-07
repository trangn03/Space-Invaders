#ifndef PLAYER_H
#define PLAYER_H

#include "opponent.h"

class Player : public GameElement {
 private:
  int width_ = 50;
  int height_ = 50;

 public:
  Player();
  Player(int x, int y);
  void Draw(graphics::Image& screen);
  void Move(const graphics::Image& player);
};

class PlayerProjectile : public GameElement {
 private:
  int width_ = 5;
  int height_ = 5;

 public:
  PlayerProjectile();
  PlayerProjectile(int x, int y);
  void Draw(graphics::Image& screen);
  void Move(const graphics::Image& p_projectile);
};
#endif
