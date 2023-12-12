#include "text_out_box.h"
#include "core.input/model/keyboard_input.h"
#include "core/model/scene_mngr.h"
#include "main_scene.gui/model/experience_bar.h"
namespace Narradia
{
    /**
     Checks if input should be activated and processes typed
     input characters.
    */
    void TextOutBox::UpdateGameLogic() {
        if (KeyboardInput::Get()->KeyHasBeenFiredPickResult(SDLK_RETURN)) {
            input_active_ = !input_active_;
        }
        if (input_active_) {
            auto new_text_input = KeyboardInput::Get()->PickTextInput();
            input_text_.insert(cursor_position_, new_text_input);
            cursor_position_ += new_text_input.length();
        }
    }

    /**
     Adds provided text with color to the internal data
     structure, being ready for rendering.
    */
    void TextOutBox::Print(std::string_view text, Color text_color) {
        if (!enabled_)
            return;
        auto printed_text = std::string(GetCurrTime().data()) + "." +
                            std::to_string(SDL_GetTicks() % 1000) + ") " + text.data();
        text_lines_.push_back({printed_text, text_color});
    }

    /**
     Calculates maximum number of text lines that can be
     displayed in the TextOutBox.
    */
    int TextOutBox::GetMaxNumLines() {
        return static_cast<int>(kBounds.h / kTextLineHeight) - 2;
    }

    int TextOutBox::GetTextLineIndex(int visible_row_index) {
        return static_cast<int>(text_lines_.size()) - GetMaxNumLines() + visible_row_index;
    }

    PointF TextOutBox::GetTextLinePosition(int visible_row_index) {
        auto used_bounds = GetUsedBounds();
        auto line_position_y = used_bounds.y + (visible_row_index + 1) * kTextLineHeight;
        return {used_bounds.x + 0.01f, line_position_y};
    }

    RectF TextOutBox::GetHorizontalSplitterRect() {
        auto used_bounds = GetUsedBounds();
        return {
            0.0f, used_bounds.y + used_bounds.h - 1.3f * kTextLineHeight, kBounds.w,
            kSplitLineHeight};
    }

    RectF TextOutBox::GetInputArrowRect() {
        auto used_bounds = GetUsedBounds();
        return {
            0.0f, used_bounds.y + used_bounds.h - 1.3f * kTextLineHeight, kTextLineHeight,
            kTextLineHeight};
    }

    PointF TextOutBox::GetInputTextPosition() {
        return GetInputArrowRect().GetPosition().Translate(
            TextOutBox::kTextLineHeight, TextOutBox::kTextLineHeight / 2);
    }

    std::string TextOutBox::GetInputTextWithCursor() {
        auto res = input_text_;
        if (SDL_GetTicks() % 600 < 300)
            res.insert(cursor_position_, "|");
        else
            res.insert(cursor_position_, " ");
        return res;
    }

    RectF TextOutBox::GetUsedBounds() {
        auto res = kBounds;
        if (SceneMngr::Get()->curr_scene() == SceneNames::Main)
            res = res.Translate(0.0f, -ExperienceBar::kBarHeight);
        return res;
    }
}
