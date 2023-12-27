#include "keyboard_movement_module.h"
#include "input/m/kb_input.h"
#include "mob_targeting_module.h"
#include "world-actors/m/player.h"

namespace Narradia
{
   void KeyboardMovementModule::UpdateGameLogic()
   {
      auto w_is_pressed = KbInput::get()->KeyIsPressed(SDLK_w);
      auto d_is_pressed = KbInput::get()->KeyIsPressed(SDLK_d);
      auto s_is_pressed = KbInput::get()->KeyIsPressed(SDLK_s);
      auto a_is_pressed = KbInput::get()->KeyIsPressed(SDLK_a);
      auto time_to_update =
          SDL_GetTicks() > Player::get()->ticks_last_move() + 400 / Player::get()->movement_speed();
      if (time_to_update && (w_is_pressed || d_is_pressed || s_is_pressed || a_is_pressed))
      {
         if (w_is_pressed)
            Player::get()->MoveForward();
         if (d_is_pressed)
            Player::get()->MoveRight();
         if (s_is_pressed)
            Player::get()->MoveBackwards();
         if (a_is_pressed)
            Player::get()->MoveLeft();
         Player::get()->set_ticks_last_move(SDL_GetTicks());
         Player::get()->set_destination({-1, -1});
         MobTargetingModule::get()->ClearTarget();
      }
   }
}
