#include "keyboard_movement_module.h"
#include "core.input/model/keyboard_input.h"
#include "world.actors/model/player.h"
namespace Narradia {
  void KeyboardMovementModule::UpdateGameLogic() {
    auto w_is_pressed = KeyboardInput::Get()->KeyIsPressed(SDLK_w);
    auto d_is_pressed = KeyboardInput::Get()->KeyIsPressed(SDLK_d);
    auto s_is_pressed = KeyboardInput::Get()->KeyIsPressed(SDLK_s);
    auto a_is_pressed = KeyboardInput::Get()->KeyIsPressed(SDLK_a);
    auto time_to_update =
        SDL_GetTicks() > Player::Get()->ticks_last_move() + 400 / Player::Get()->movement_speed();
    if (time_to_update && (w_is_pressed || d_is_pressed || s_is_pressed || a_is_pressed)) {
      if (w_is_pressed)
        Player::Get()->MoveForward();
      if (d_is_pressed)
        Player::Get()->MoveRight();
      if (s_is_pressed)
        Player::Get()->MoveBackwards();
      if (a_is_pressed)
        Player::Get()->MoveLeft();
      Player::Get()->set_ticks_last_move(SDL_GetTicks());
      Player::Get()->set_destination({-1, -1});
    }
  }
}
