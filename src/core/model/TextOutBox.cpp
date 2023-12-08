#include "TextOutBox.h"
#include "core.input/model/KeyboardInput.h"

namespace Narradia {
    /**
     * Checks if input should be activated and processes typed input characters.
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
     * Adds provided text with color to the internal data structure, being ready
     * for rendering.
     */
    void TextOutBox::Print(std::string_view text, Color text_color) {
        if (!enabled_)
            return;
        std::string printed_text = std::string(GetCurrTime().data()) + "." +
                                   std::to_string(SDL_GetTicks() % 1000) + ") " + text.data();
        text_lines_.push_back({printed_text, text_color});
    }

    /**
     * Calculates maximum number of text lines that can be displayed in the
     * TextOutBox.
     */
    int TextOutBox::GetMaxNumLines() {
        return static_cast<int>(kBounds.height / kTextLineHeight) - 2;
    }
}
