#pragma once
#include <SDL2/SDL.h>
#include <set>
#include <string>
namespace Narradia
{
   class KbInput : public Singleton<KbInput>
   {
     public:
      auto OnKeyPress(SDL_Keycode key) -> void;

      auto OnKeyRelease(SDL_Keycode key) -> void;

      auto KeyIsPressed(SDL_Keycode key) -> bool;

      auto KeyHasBeenFiredPickResult(SDL_Keycode key) -> bool;

      auto AnyKeyIsPressedPickResult() -> bool;

      auto AppendTextInput(std::string_view to_append) -> void;

      auto PickTextInput() -> std::string_view;

     private:
      std::set<SDL_Keycode> pressed_keys_;
      std::set<SDL_Keycode> fired_keys_;
      std::string text_input_;
   };
}
