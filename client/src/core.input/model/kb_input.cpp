#include "kb_input.h"
namespace Narradia
{
    /**
     Register that a key has been pressed.
    */
    void KbInput::OnKeyPress(SDL_Keycode key) {
        pressed_keys_.insert(key);
        fired_keys_.insert(key);
    }

    /**
     Register that a key has been released.
    */
    void KbInput::OnKeyRelease(SDL_Keycode key) {
        pressed_keys_.erase(key);
    }

    /**
     Returns state for a key being pressed or not..
    */
    bool KbInput::KeyIsPressed(SDL_Keycode key) {
        return pressed_keys_.count(key);
    }

    /**
     Returns state for if a key has been fired, and resets
     the state afterwards.
    */
    bool KbInput::KeyHasBeenFiredPickResult(SDL_Keycode key) {
        auto result = fired_keys_.count(key) > 0;
        fired_keys_.erase(key);
        return result;
    }

    /**
     Returns state for if any key at all is being pressed.
    */
    bool KbInput::AnyKeyIsPressedPickResult() {
        auto result = pressed_keys_.size() > 0;
        pressed_keys_.clear();
        return result;
    }

    /**
     Appends text input to the already typed text not yet
     been extracted.
    */
    void KbInput::AppendTextInput(std::string_view to_append) {
        text_input_.append(to_append);
    }

    /**
     Picks the typed text and returns it. Clears the
     internally stored text input value at the same time.
    */
    std::string_view KbInput::PickTextInput() {
        auto result = text_input_;
        text_input_ = "";
        return result;
    }
}
