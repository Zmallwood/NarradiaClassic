#pragma once
#include <SDL2/SDL.h>
#include <set>
#include <string>
namespace Narradia
{
   class KbInput : public Singleton<KbInput>
   {
     public:
      void OnKeyPress(SDL_Keycode key);

      void OnKeyRelease(SDL_Keycode key);

      bool KeyIsPressed(SDL_Keycode key);

      bool KeyHasBeenFiredPickResult(SDL_Keycode key);

      bool AnyKeyIsPressedPickResult();

      void AppendTextInput(std::string_view to_append);

      std::string_view PickTextInput();

     private:
      std::set<SDL_Keycode> pressed_keys_;
      std::set<SDL_Keycode> fired_keys_;
      std::string text_input_;
   };
}
