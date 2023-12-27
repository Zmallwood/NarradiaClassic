#if 1
#include "console.h"
#include "core.h"
#include "main_scene-gui/experience_bar.h"
#endif

namespace Narradia
{
   auto Console::UpdateGameLogic() -> void
   {
      if (KbInput::get()->KeyHasBeenFiredPickResult(SDLK_RETURN))
      {
         input_active_ = !input_active_;
      }
      if (input_active_)
      {
         auto new_text_input = KbInput::get()->PickTextInput();
         input_text_.insert(cursor_position_, new_text_input);
         cursor_position_ += new_text_input.length();
      }
   }
   auto Console::Print(std::string_view text, Color text_color) -> void
   {
      if (!enabled_)
         return;
      auto printed_text = std::string(CurrTime().data()) + "." +
                          std::to_string(SDL_GetTicks() % 1000) + ") " + text.data();
      text_lines_.push_back({printed_text, text_color});
   }
   auto Console::InputTextWithCursor() -> std::string
   {
      auto res = input_text_;
      if (SDL_GetTicks() % 600 < 300)
         res.insert(cursor_position_, "|");
      else
         res.insert(cursor_position_, " ");
      return res;
   }
   auto Console::Bounds() -> RectF
   {
      return SceneMngr::get()->curr_scene() == SceneNames::Main
                 ? kDefaultBounds.Translate(0.0f, -ExperienceBar::kBarHeight)
                 : kDefaultBounds;
   }
}
