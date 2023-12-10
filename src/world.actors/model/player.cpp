#include "player.h"
#include "conf/model/conf.h"
#include "world.structure/model/world.h"

namespace Narradia {
  /**
   Set default spawn coordinate.
  */
  Player::Player() {
    position_ = {kMapWidth / 2.0f, 0.0f, kMapHeight / 2.0f};
  }

  void Player::MoveForward() {
    MoveAtAngle(0.0f);
  }

  void Player::MoveRight() {
    MoveAtAngle(90.0f);
  }

  void Player::MoveBackwards() {
    MoveAtAngle(180.0f);
  }

  void Player::MoveLeft() {
    MoveAtAngle(-90.0f);
  }

  void Player::MoveAtAngle(float angle_deg_) {
    auto used_angle = angle_deg_ - facing_angle_deg_;
    auto dx = CosDeg(used_angle + 90.0f) * step_size_;
    auto dz = SinDeg(used_angle + 90.0f) * step_size_;
    auto new_x = position_.x + dx;
    auto new_z = position_.z + dz;
    if (new_x < 0 || new_z < 0 || new_x >= kMapWidth || new_z >= kMapHeight)
      return;
    auto map_area = World::Get()->curr_map_area();
    auto new_coord = Point{static_cast<int>(new_x), static_cast<int>(new_z)};
    if (map_area->GetTile(new_coord)->ground() == "GroundWater")
      return;
    position_.x = new_x;
    position_.z = new_z;
  }
}
