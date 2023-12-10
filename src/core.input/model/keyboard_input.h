#pragma once

namespace Narradia {
  /**
   Model for keyboard_input.holding keyboard input state,
   has no controller or view.
  */
  class KeyboardInput : public Singleton<KeyboardInput> {
   public:
    void RegisterPressedKey(SDL_Keycode key);
    void RegisterReleasedKey(SDL_Keycode key);
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
