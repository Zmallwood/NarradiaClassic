#if 1
#include "player.h"
#include "conf/consts.h"
#include "core/console.h"
#include "main_scene-modules-world_view/camera.h"
#include "world-struct.h"
#include "comm/math_sys.h"
#endif

namespace Narradia
{
   Player::Player()
   {
      position_ = {0, 0};
   }
   void Player::MoveForward()
   {
      facing_angle_deg_ = Camera::get()->horizontal_angle_deg();
      MoveAtAngle(0.0f);
   }
   void Player::MoveRight()
   {
      facing_angle_deg_ = Camera::get()->horizontal_angle_deg();
      MoveAtAngle(90.0f);
   }
   void Player::MoveBackwards()
   {
      facing_angle_deg_ = Camera::get()->horizontal_angle_deg();
      MoveAtAngle(180.0f);
   }
   void Player::MoveLeft()
   {
      facing_angle_deg_ = Camera::get()->horizontal_angle_deg();
      MoveAtAngle(-90.0f);
   }
   void Player::AddExperience(int amount)
   {
      experience_ += amount;
      Console::get()->Print("You got " + std::to_string(amount) + " experience");
   }
   void Player::MoveAtAngle(float angle_deg_)
   {
      auto map_area = World::get()->CurrMapArea();
      auto used_angle = angle_deg_ - facing_angle_deg_;
      auto dx = CosDeg(used_angle + 90.0f) * step_size_;
      auto dz = SinDeg(used_angle + 90.0f) * step_size_;
      auto new_x = position_.x + dx;
      auto new_z = position_.z + dz;
      if (new_x < 0 || new_z < 0 || new_x >= map_area->GetWidth() || new_z >= map_area->GetHeight())
         return;
      auto new_coord = Point{static_cast<int>(new_x), static_cast<int>(new_z)};
      if (map_area->GetTile(new_coord)->ground() == "GroundWater")
         return;
      position_.x = new_x;
      position_.z = new_z;
   }
   bool Player::IsMoving()
   {
      return SDL_GetTicks() < ticks_last_move_ + 400 / movement_speed_;
   }
   void Player::Hit(float damage)
   {
      health_ -= damage;
   }
}
