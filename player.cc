#include "player.h"

// Player
Player::Player() : GameElement{0, 0, 50, 50} {}
Player::Player(int x, int y) : GameElement{x, y, 50, 50} {}
void Player::Draw(graphics::Image& screen) {
  screen.DrawRectangle(GetX(), GetY(), 50, 50, 219, 45, 42);      // red
  screen.DrawRectangle(GetX() + 7, GetY() + 6, 8, 10, 0, 0, 0);   // left eyes
  screen.DrawRectangle(GetX() + 35, GetY() + 6, 8, 10, 0, 0, 0);  // right eyes
  screen.DrawRectangle(GetX() + 7, GetY() + 30, 8, 9, 0, 0, 0);
  screen.DrawRectangle(GetX() + 35, GetY() + 30, 8, 9, 0, 0, 0);
  screen.DrawRectangle(GetX() + 7, GetY() + 36, 36, 8, 0, 0, 0);
}

void Player::Move(const graphics::Image& player) {}

// Player Projectile
PlayerProjectile::PlayerProjectile() : GameElement{0, 0, 5, 5} {}
PlayerProjectile::PlayerProjectile(int x, int y) : GameElement{x, y, 5, 5} {}
void PlayerProjectile::Draw(graphics::Image& screen) {
  screen.DrawRectangle(GetX(), GetY(), 5, 5, 204, 51, 255);  // purple
}

void PlayerProjectile::Move(const graphics::Image& p_projectile_) {
  SetY(GetY() - 4);
  if (IsOutOfBounds(p_projectile_)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
