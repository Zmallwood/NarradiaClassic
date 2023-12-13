#include "text_out_box.h"
namespace Narradia
{
   auto TextOutBox::UpdateGameLogic() -> void {
      if (KbInput::get()->KeyHasBeenFiredPickResult(SDLK_RETURN)) {
         input_active_ = !input_active_;
      }
      if (input_active_) {
         auto new_text_input = KbInput::get()->PickTextInput();
         input_text_.insert(cursor_position_, new_text_input);
         cursor_position_ += new_text_input.length();
      }
   }

   auto TextOutBox::Print(std::string_view text, Color text_color) -> void {
      if (!enabled_)
         return;
      auto printed_text = std::string(CurrTime().data()) + "." +
                          std::to_string(SDL_GetTicks() % 1000) + ") " + text.data();
      text_lines_.push_back({printed_text, text_color});
   }

   auto TextOutBox::MaxNumLines() -> int {
      return static_cast<int>(kDefaultBounds.h / kTextLineHeight) - 2;
   }

   auto TextOutBox::TextLineIndex(int visible_row_index) -> int {
      return static_cast<int>(text_lines_.size()) - MaxNumLines() + visible_row_index;
   }

   auto TextOutBox::TextLinePosition(int visible_row_index) -> PointF {
      auto line_position_y = Bounds().y + (visible_row_index + 1) * kTextLineHeight;
      return {Bounds().x + 0.01f, line_position_y};
   }

   auto TextOutBox::HorizontalSplitterRect() -> RectF {
      return {
          0.0f, Bounds().y + Bounds().h - 1.3f * kTextLineHeight, kDefaultBounds.w,
          kSplitLineHeight};
   }

   auto TextOutBox::InputArrowRect() -> RectF {
      return {
          0.0f, Bounds().y + Bounds().h - 1.3f * kTextLineHeight, kTextLineHeight, kTextLineHeight};
   }

   auto TextOutBox::InputTextPosition() -> PointF {
      return InputArrowRect().GetPosition().Translate(
          TextOutBox::kTextLineHeight, TextOutBox::kTextLineHeight / 2);
   }

   auto TextOutBox::InputTextWithCursor() -> std::string {
      auto res = input_text_;
      if (SDL_GetTicks() % 600 < 300)
         res.insert(cursor_position_, "|");
      else
         res.insert(cursor_position_, " ");
      return res;
   }

   auto TextOutBox::Bounds() -> RectF {
      return SceneMngr::get()->curr_scene() == SceneNames::Main
                 ? kDefaultBounds.Translate(0.0f, -ExperienceBar::kBarHeight)
                 : kDefaultBounds;
   }
}
