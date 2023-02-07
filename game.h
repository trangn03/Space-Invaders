#ifndef GAME_H
#define GAME_H

#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 private:
  graphics::Image screen_;
  std::vector<std::unique_ptr<Opponent>> opponent_;
  std::vector<std::unique_ptr<OpponentProjectile>> o_projectile_;
  std::vector<std::unique_ptr<PlayerProjectile>> p_projectile_;
  Player player_;
  int score_ = 0;
  bool lost_ = false;

 public:
  void CreateOpponents();
  void Init();
  void UpdateScreen();
  void Start();
  void FilterIntersections();
  void MoveGameElements();
  void OnAnimationStep();
  void OnMouseEvent(const graphics::MouseEvent& m);
  void LaunchProjectiles();
  void RemoveInactive();
  Game();
  Game(int w, int h);
  graphics::Image& GetGameScreen();
  std::vector<std::unique_ptr<Opponent>>& GetOpponents();
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles();
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles();
  Player& GetPlayer();
  int GetScore();
  bool HasLost();
};
#endif
