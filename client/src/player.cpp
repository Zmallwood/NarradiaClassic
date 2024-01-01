#if 1
#include "player.h"
#include "adds-world_view.h"
#include "calc.h"
#include "conf.h"
#include "core.h"
#include "rend_tiles_v.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   // Player
#if 1

   Player::Player() {
      pos_ = {0, 0};
   }

   void Player::MoveForward() {
      facing_angle_deg_ = Camera::get()->horizontal_angle_deg();
      MoveAtAngle(0.0f);
   }

   void Player::MoveRight() {
      facing_angle_deg_ = Camera::get()->horizontal_angle_deg();
      MoveAtAngle(90.0f);
   }

   void Player::MoveBackwards() {
      facing_angle_deg_ = Camera::get()->horizontal_angle_deg();
      MoveAtAngle(180.0f);
   }

   void Player::MoveLeft() {
      facing_angle_deg_ = Camera::get()->horizontal_angle_deg();
      MoveAtAngle(-90.0f);
   }

   void Player::AddExperience(int amount) {
      experience_ += amount;
      Console::get()->Print("You got " + std::to_string(amount) + " experience");
   }

   void Player::MoveAtAngle(float angle_deg_) {
      try {
         auto map_area = World::get()->CurrWorldArea();
         auto used_angle = angle_deg_ - facing_angle_deg_;
         auto dx = CosDeg(used_angle + 90.0f) * step_size_;
         auto dz = SinDeg(used_angle + 90.0f) * step_size_;
         auto new_x = pos_.x + dx;
         auto new_z = pos_.z + dz;
         // if (new_x < 0 || new_z < 0 || new_x >= map_area->Width() || new_z >=
         // map_area->Height())
         if (new_z < 0 || new_x >= map_area->Width() || new_z >= map_area->Height())
            return;
         auto new_coord = Point{static_cast<int>(new_x), static_cast<int>(new_z)};
         if (new_coord.x < 0) {
            new_coord.x += map_area->Width();
            new_x += map_area->Width();
            for (auto y = world_location_.y - 1; y <= world_location_.y + 1; y++) {
               for (auto x = world_location_.x - 1; x <= world_location_.x + 1; x++) {
                  if (World::get()->WorldAreaAt({x, y}))
                     World::get()->WorldAreaAt({x, y})->ClearAllRIDs();
               }
            }
            world_location_.x--;
            map_area = World::get()->CurrWorldArea();
            WorldViewAddV::Dispose();
            RendTilesV::Dispose();
         }
         if (map_area->GetTile(new_coord)->ground() == "GroundWater")
            return;
         pos_.x = new_x;
         pos_.z = new_z;
      }
      catch (std::exception &e) {
         Console::get()->Print("Exception in Player::MoveAtAngle: " + std::string(e.what()));
      }
   }

   bool Player::IsMoving() {
      return SDL_GetTicks() < ticks_last_move_ + 400 / movement_speed_;
   }

   void Player::Hit(float damage) {
      health_ -= damage;
   }

#endif
}
