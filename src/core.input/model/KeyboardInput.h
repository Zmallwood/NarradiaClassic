#pragma once

namespace Narradia {
    /**
     * Model for KeyboardInput holding keyboard input state, has no controller
     * or view.
     */
    class KeyboardInput : public Singleton<KeyboardInput> {
      public:
        void RegisterPressedKey(SDL_Keycode key);

        void RegisterReleasedKey(SDL_Keycode key);

        bool KeyIsPressed(SDL_Keycode key);

        bool KeyHasBeenFiredPickResult(SDL_Keycode key);

        bool AnyKeyIsPressedPickResult();

      private:
        std::set<SDL_Keycode> pressed_keys_;
        std::set<SDL_Keycode> fired_keys_;
    };
}
