#include "MouseMovementModule.h"
#include "TileHoveringModule.h"
#include "core.input/model/MouseInput.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"

namespace Narradia {
    void MouseMovementModule::UpdateGameLogic() {
        if (MouseInput::Get()->left_button()->HasBeenFiredPickResult()) {
            Player::Get()->set_destination(
                TileHoveringModule::Get()->hovered_tile());
        }

        auto destination = Player::Get()->destination();

        auto time_to_update =
            SDL_GetTicks() > Player::Get()->ticks_last_move() +
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

                auto map_area = World::Get()->curr_map_area();

                if (map_area->GetTile(new_x, new_y)->ground() !=
                    "GroundWater") {
                    if (map_area->GetTile(new_x, new_y)->object() == nullptr) {
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