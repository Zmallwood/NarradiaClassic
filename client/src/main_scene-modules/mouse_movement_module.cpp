#if 1
#include "mouse_movement_module.h"
#include "core.h"
#include "mob_targeting_module.h"
#include "tile_hovering_module.h"
#include "actors.h"
#endif

namespace Narradia
{
   void MouseMovementModule::UpdateGameLogic()
   {
      MouseInput::get()->left_btn()->AddFiredAction(
          []
          {
             Player::get()->set_destination(TileHoveringModule::get()->hovered_tile());
             MobTargetingModule::get()->ClearTarget();
          },
          5);
      auto destination = Player::get()->destination();
      if (destination.x == -1 && destination.y == -1)
         return;
      auto time_to_update =
          SDL_GetTicks() > Player::get()->ticks_last_move() + 400 / Player::get()->movement_speed();
      if (time_to_update)
      {
         auto dx = destination.x + 0.5f - Player::get()->position().x;
         auto dy = destination.y + 0.5f - Player::get()->position().z;
         auto abs_dx = std::abs(dx);
         auto abs_dy = std::abs(dy);
         if (abs_dx < 0.5f && abs_dy < 0.5f)
         {
            Player::get()->set_destination({-1, -1});
            return;
         }
         auto base_angle_deg = std::atan2(dy, dx) * 180.0f / M_PI - 90.0f;
         Player::get()->set_facing_angle_deg(-base_angle_deg);
         auto angle_deg = base_angle_deg + Player::get()->facing_angle_deg();
         Player::get()->MoveAtAngle(angle_deg);
         Player::get()->set_ticks_last_move(SDL_GetTicks());
      }
   }
}
