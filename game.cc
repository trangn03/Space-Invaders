#include "game.h"

#include <stdlib.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

Game::Game() : screen_{800, 600} {}
Game::Game(int w, int h) : screen_{w, h} {}
graphics::Image& Game::GetGameScreen() { return screen_; }
std::vector<std::unique_ptr<Opponent>>& Game::GetOpponents() {
  return opponent_;
}
std::vector<std::unique_ptr<OpponentProjectile>>&
Game::GetOpponentProjectiles() {
  return o_projectile_;
}
std::vector<std::unique_ptr<PlayerProjectile>>& Game::GetPlayerProjectiles() {
  return p_projectile_;
}
Player& Game::GetPlayer() { return player_; }

int Game::GetScore() { return score_; }

bool Game::HasLost() { return lost_; }

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> opponent1 = std::make_unique<Opponent>(50, 50);
  std::unique_ptr<Opponent> opponent2 = std::make_unique<Opponent>(140, 50);
  std::unique_ptr<Opponent> opponent3 = std::make_unique<Opponent>(230, 50);
  std::unique_ptr<Opponent> opponent4 = std::make_unique<Opponent>(320, 50);
  std::unique_ptr<Opponent> opponent5 = std::make_unique<Opponent>(410, 50);
  opponent_.push_back(std::move(opponent1));
  opponent_.push_back(std::move(opponent2));
  opponent_.push_back(std::move(opponent3));
  opponent_.push_back(std::move(opponent4));
  opponent_.push_back(std::move(opponent5));
}

void Game::Init() {
  player_.SetX(100);
  player_.SetY(80);
  screen_.AddMouseEventListener(*this);
  screen_.AddAnimationEventListener(*this);
}

void Game::Start() { screen_.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive()) {
      opponent_[i]->Move(screen_);
    }
  }
  for (int i = 0; i < o_projectile_.size(); i++) {
    if (o_projectile_[i]->GetIsActive()) {
      o_projectile_[i]->Move(screen_);
    }
  }
  for (int i = 0; i < p_projectile_.size(); i++) {
    if (p_projectile_[i]->GetIsActive()) {
      p_projectile_[i]->Move(screen_);
    }
  }
}

void Game::FilterIntersections() {
  // Player and Opponent
  for (int i = 0; i < opponent_.size(); i++) {
    if (player_.IntersectsWith(opponent_[i].get())) {
      player_.SetIsActive(false);
      opponent_[i]->SetIsActive(false);
      lost_ = true;
    }
  }
  // PlayerProjectile and Opponent
  for (int i = 0; i < p_projectile_.size(); i++) {
    for (int j = 0; j < opponent_.size(); j++) {
      if (p_projectile_[i]->IntersectsWith(opponent_[j].get())) {
        p_projectile_[i]->SetIsActive(false);
        opponent_[j]->SetIsActive(false);
        if (player_.GetIsActive()) {
          score_++;
        }
      }
    }
  }
  // OpponentProjectile and Player
  for (int i = 0; i < o_projectile_.size(); i++) {
    if (player_.IntersectsWith(o_projectile_[i].get())) {
      player_.SetIsActive(false);
      o_projectile_[i]->SetIsActive(false);
      lost_ = true;
    }
  }
}

void Game::UpdateScreen() {
  screen_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  std::string text = "Score: " + std::to_string(GetScore());
  screen_.DrawText(0, 0, text, 21, 0, 0, 0);
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive() == true) {
      opponent_[i]->Draw(screen_);
    }
  }
  for (int i = 0; i < o_projectile_.size(); i++) {
    if (o_projectile_[i]->GetIsActive() == true) {
      o_projectile_[i]->Draw(screen_);
    }
  }
  for (int i = 0; i < p_projectile_.size(); i++) {
    if (p_projectile_[i]->GetIsActive() == true) {
      p_projectile_[i]->Draw(screen_);
    }
  }
  if (player_.GetIsActive() == true) {
    player_.Draw(screen_);
  }
  if (HasLost()) {
    screen_.DrawText(250, 250, "Game Over", 65, 0, 0, 0);
    lost_ = true;
  }
}

void Game::RemoveInactive() {
  for (int i = opponent_.size() - 1; i >= 0; i--) {
    if (opponent_[i]->GetIsActive() == false) {
      opponent_.erase(opponent_.begin() + i);
    }
  }
  for (int i = o_projectile_.size() - 1; i >= 0; i--) {
    if (o_projectile_[i]->GetIsActive() == false) {
      o_projectile_.erase(o_projectile_.begin() + i);
    }
  }
  for (int i = p_projectile_.size() - 1; i >= 0; i--) {
    if (p_projectile_[i]->GetIsActive() == false) {
      p_projectile_.erase(p_projectile_.begin() + i);
    }
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent_.size(); i++) {
    std::unique_ptr<OpponentProjectile> op = opponent_[i]->LaunchProjectile();
    if (op != nullptr) {
      o_projectile_.push_back(std::move(op));
    }
  }
}

void Game::OnAnimationStep() {
  if (opponent_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen_.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent& m) {
  std::unique_ptr<PlayerProjectile> pp;
  if (m.GetX() > 0 && m.GetX() < screen_.GetWidth()) {
    player_.SetX(m.GetX() - player_.GetWidth() / 2);
  }
  if (m.GetY() > 0 && m.GetY() < screen_.GetHeight()) {
    player_.SetY(m.GetY() - player_.GetHeight() / 2);
  }
  if (m.GetMouseAction() == graphics::MouseAction::kPressed) {
    pp = std::make_unique<PlayerProjectile>(m.GetX(), m.GetY());
    p_projectile_.push_back(std::move(pp));
  }
  if (m.GetMouseAction() == graphics::MouseAction::kDragged) {
    pp = std::make_unique<PlayerProjectile>(m.GetX(), m.GetY());
    p_projectile_.push_back(std::move(pp));
  }
}
