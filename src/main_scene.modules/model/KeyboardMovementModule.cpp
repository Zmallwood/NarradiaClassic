#include "KeyboardMovementModule.h"
#include "core.input/model/KeyboardInput.h"
#include "world.actors/model/Player.h"

namespace Narradia {
    void KeyboardMovementModule::UpdateGameLogic() {
        auto up_is_pressed = KeyboardInput::Get()->KeyIsPressed(SDLK_UP);
        auto right_is_pressed = KeyboardInput::Get()->KeyIsPressed(SDLK_RIGHT);
        auto down_is_pressed = KeyboardInput::Get()->KeyIsPressed(SDLK_DOWN);
        auto left_is_pressed = KeyboardInput::Get()->KeyIsPressed(SDLK_LEFT);
        auto time_to_update =
            SDL_GetTicks() > Player::Get()->ticks_last_move() +
                                 400 / Player::Get()->movement_speed();

        if (time_to_update && (up_is_pressed || right_is_pressed ||
                               down_is_pressed || left_is_pressed)) {
            if (up_is_pressed)
                Player::Get()->MoveUp();

            if (right_is_pressed)
                Player::Get()->MoveRight();

            if (down_is_pressed)
                Player::Get()->MoveDown();

            if (left_is_pressed)
                Player::Get()->MoveLeft();

            Player::Get()->set_ticks_last_move(SDL_GetTicks());
        }
    }
}