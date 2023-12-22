#include "kb_input.h"
namespace Narradia
{
   auto KbInput::OnKeyPress(SDL_Keycode key) -> void {
      pressed_keys_.insert(key);
      fired_keys_.insert(key);
   }

   auto KbInput::OnKeyRelease(SDL_Keycode key) -> void {
      pressed_keys_.erase(key);
   }

   auto KbInput::KeyIsPressed(SDL_Keycode key) -> bool {
      return pressed_keys_.count(key);
   }

   auto KbInput::KeyHasBeenFiredPickResult(SDL_Keycode key) -> bool {
      auto result = fired_keys_.count(key) > 0;
      fired_keys_.erase(key);
      return result;
   }

   auto KbInput::AnyKeyIsPressedPickResult() -> bool {
      auto result = pressed_keys_.size() > 0;
      pressed_keys_.clear();
      return result;
   }

   auto KbInput::AppendTextInput(std::string_view to_append) -> void {
      text_input_.append(to_append);
   }

   auto KbInput::PickTextInput() -> std::string_view {
      auto result = text_input_;
      text_input_ = "";
      return result;
   }
}
