#include "mouse_movement_module.h"
#include "conf.world/model/objects_conf.h"
#include "conf/model/conf.h"
#include "core.input/model/mouse_input.h"
#include "main_scene.modules.world_view/model/camera.h"
#include "mob_targeting_module.h"
#include "tile_hovering_module.h"
#include "world.actors/model/player.h"
#include "world.structure/model/world.h"

namespace Narradia {
  void MouseMovementModule::UpdateGameLogic() {
    MouseInput::Get()->left_button()->AddFiredAction(
        [] {
          Player::Get()->set_destination(TileHoveringModule::Get()->hovered_tile());
          MobTargetingModule::Get()->ClearTarget();
        },
        5);
    auto destination = Player::Get()->destination();
    if (destination.x == -1 && destination.y == -1)
      return;
    auto time_to_update =
        SDL_GetTicks() > Player::Get()->ticks_last_move() + 400 / Player::Get()->movement_speed();
    if (time_to_update) {
      auto dx = destination.x + 0.5f - Player::Get()->position().x;
      auto dy = destination.y + 0.5f - Player::Get()->position().z;
      auto abs_dx = std::abs(dx);
      auto abs_dy = std::abs(dy);
      if (abs_dx < 0.5f && abs_dy < 0.5f) {
        Player::Get()->set_destination({-1, -1});
        return;
      }
      auto base_angle_deg = std::atan2(dy, dx) * 180.0f / M_PI - 90.0f;
      Player::Get()->set_facing_angle_deg(-base_angle_deg);
      auto angle_deg = base_angle_deg + Camera::Get()->horizontal_angle_deg() +
                       Player::Get()->facing_angle_deg();
      Player::Get()->MoveAtAngle(angle_deg);
      Player::Get()->set_ticks_last_move(SDL_GetTicks());
    }
  }
}
