#include "kb_input.h"

namespace Narradia
{
   void KbInput::OnKeyPress(SDL_Keycode key) 
   {
      pressed_keys_.insert(key);
      fired_keys_.insert(key);
   }

   void KbInput::OnKeyRelease(SDL_Keycode key)
   {
      pressed_keys_.erase(key);
   }

   bool KbInput::KeyIsPressed(SDL_Keycode key) 
   {
      return pressed_keys_.count(key);
   }

   bool KbInput::KeyHasBeenFiredPickResult(SDL_Keycode key)
   {
      auto result = fired_keys_.count(key) > 0;
      fired_keys_.erase(key);
      return result;
   }

   bool KbInput::AnyKeyIsPressedPickResult() 
   {
      auto result = pressed_keys_.size() > 0;
      pressed_keys_.clear();
      return result;
   }

   void KbInput::AppendTextInput(std::string_view to_append) 
   {
      text_input_.append(to_append);
   }

   std::string_view KbInput::PickTextInput() 
   {
      auto result = text_input_;
      text_input_ = "";
      return result;
   }
}
