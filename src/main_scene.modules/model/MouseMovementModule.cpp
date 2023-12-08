#include "MouseMovementModule.h"
#include "MobTargetingModule.h"
#include "configuration.world/model/ObjectsConfiguration.h"
#include "configuration/model/Configuration.h"
#include "core.input/model/MouseInput.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"

namespace Narradia {
    void MouseMovementModule::UpdateGameLogic() {
        //        MouseInput::Get()->left_button()->AddFiredAction([] {
        //            if (MouseInput::Get()->left_button()->is_pressed()) {
        //                Player::Get()->set_destination(
        //                    TileHoveringModule::Get()->hovered_tile());
        //                MobTargetingModule::Get()->ClearTarget();
        //            }
        //        });
        auto destination = Player::Get()->destination();
        auto time_to_update = SDL_GetTicks() > Player::Get()->ticks_last_move() +
                                                   400 / Player::Get()->movement_speed();
        if (time_to_update) {
            if (destination.x != -1 && destination.y != -1) {
                auto dx = destination.x - Player::Get()->position().x;
                auto dy = destination.y - Player::Get()->position().y;
                auto abs_dx = std::abs(dx);
                auto abs_dy = std::abs(dy);
                auto norm_x = dx ? dx / abs_dx : 0;
                auto norm_y = dy ? dy / abs_dy : 0;
                auto new_x = Player::Get()->position().x + norm_x;
                auto new_y = Player::Get()->position().y + norm_y;
                if (new_x < 0 || new_y < 0 || new_x >= kMapWidth || new_y >= kMapHeight)
                    return;
                auto map_area = World::Get()->curr_map_area();
                if (map_area->GetTile(new_x, new_y)->ground() != "GroundWater") {
                    auto is_obstacle = false;
                    if (map_area->GetTile(new_x, new_y)->object())
                        is_obstacle = ObjectsConfiguration::Get()->IsObstacle(
                            map_area->GetTile(new_x, new_y)->object()->type());
                    if (!is_obstacle) {
                        if (norm_y == -1)
                            Player::Get()->MoveUp();
                        else if (norm_y == 1)
                            Player::Get()->MoveDown();
                        if (norm_x == 1)
                            Player::Get()->MoveRight();
                        else if (norm_x == -1)
                            Player::Get()->MoveLeft();
                        Player::Get()->set_ticks_last_move(SDL_GetTicks());
                    }
                }
            }
        }
    }
}
