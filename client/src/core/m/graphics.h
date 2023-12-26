#pragma once
namespace Narradia
{
   class Graphics : public Singleton<Graphics>
   {
     public:
      auto win()
      {
         return win_;
      }

      void set_win(std::shared_ptr<SDL_Window> value)
      {
         win_ = value;
      }

      auto win_size()
      {
         return win_size_;
      }

      auto win_flags()
      {
         return win_flags_;
      }

      auto clear_color()
      {
         return clear_color_;
      }

     private:
      std::shared_ptr<SDL_Window> win_;
      Size win_size_ = {660, 660};
      Uint32 win_flags_ = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
      Color clear_color_ = {0, 150, 255, 255};
   };
}
