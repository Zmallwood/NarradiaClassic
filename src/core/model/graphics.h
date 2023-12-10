#pragma once

namespace Narradia {
  /**
   Model for Graphics, has a view but no controller.
  */
  class Graphics : public Singleton<Graphics> {
   public:
    auto window() {
      return window_;
    }

    void set_window(std::shared_ptr<SDL_Window> value) {
      window_ = value;
    }

    auto window_size() {
      return window_size_;
    }

    auto window_flags() {
      return window_flags_;
    }

    auto clear_color() {
      return clear_color_;
    }

   private:
    std::shared_ptr<SDL_Window> window_;
    Size window_size_ = {660, 660};
    Uint32 window_flags_ = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
    Color clear_color_ = {0, 150, 255, 255};
  };
}
