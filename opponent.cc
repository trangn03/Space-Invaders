#include "opponent.h"

#include <memory>
#include <vector>

#include "cpputils/graphics/image.h"

// Opponent
Opponent::Opponent() : GameElement{0, 0, 50, 50} {}
Opponent::Opponent(int x, int y) : GameElement{x, y, 50, 50} {}
void Opponent::Draw(graphics::Image& screen) {
  screen.DrawRectangle(GetX(), GetY(), 50, 50, 52, 180, 235);
  screen.DrawRectangle(GetX() + 7, GetY() + 6, 8, 20, 255, 235, 20);
  screen.DrawRectangle(GetX() + 35, GetY() + 6, 8, 20, 255, 235, 20);
  screen.DrawRectangle(GetX() + 7, GetY() + 35, 36, 8, 255, 235, 20);
}

void Opponent::Move(const graphics::Image& opponent) {
  SetX(GetX() + 2);
  SetY(GetY() + 2);
  if (IsOutOfBounds(opponent)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}

std::unique_ptr<class OpponentProjectile> Opponent::LaunchProjectile() {
  std::unique_ptr<class OpponentProjectile> op;
  if (count >= 9) {
    count = 0;
    op = std::make_unique<class OpponentProjectile>(GetX(), GetY());
    return std::move(op);
  } else {
    count++;
    return nullptr;
  }
}

// Opponent Projectile
OpponentProjectile::OpponentProjectile() : GameElement{0, 0, 5, 5} {}
OpponentProjectile::OpponentProjectile(int x, int y)
    : GameElement{x, y, 5, 5} {}
void OpponentProjectile::Draw(graphics::Image& screen) {
  screen.DrawRectangle(GetX(), GetY(), 5, 5, 255, 153, 102);  // orange
}
void OpponentProjectile::Move(const graphics::Image& o_projectile_) {
  SetY(GetY() + 3);
  SetX(GetX() + 3);
  if (IsOutOfBounds(o_projectile_)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
