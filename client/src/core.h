#pragma once

namespace Narradia
{
   class Engine : public S<Engine>
   {
     public:
      Engine();
      void UpdateGameLogic();
      void Finalize();
      auto is_running()
      {
         return is_running_;
      }
      void set_running(bool value)
      {
         is_running_ = value;
      }
      auto title()
      {
         return title_;
      }

     private:
      bool is_running_ = true;
      std::string_view title_ = "Narradia";
   };

   class FPSCapper : public S<FPSCapper>
   {
     public:
      auto Below60FPS() -> bool;

     private:
      int prev_ticks_ = 0;
   };

   enum class SceneNames
   {
      None,
      Intro,
      MainMenu,
      Main,
      MapOverviewGen
   };

   class IScene;

   class SceneMngr : public S<SceneMngr>
   {
     public:
      SceneMngr();
      void UpdateGameLogicCurrScene();
      void FinalizeCurrScene();
      auto curr_scene()
      {
         return curr_scene_;
      }
      void set_curr_scene(SceneNames value)
      {
         curr_scene_ = value;
      }
      auto curr_scene_canceled()
      {
         return curr_scene_canceled_;
      }
      void set_curr_scene_canceled(bool value)
      {
         curr_scene_canceled_ = value;
      }

     private:
      std::map<SceneNames, std::shared_ptr<IScene>> scenes_;
      SceneNames curr_scene_ = SceneNames::None;
      bool curr_scene_canceled_ = false;
   };

   class SceneGui;

   class IScene
   {
     public:
      IScene();
      void UpdateGameLogic();
      virtual void Finalize() = 0;
      auto scene_gui()
      {
         return scene_gui_;
      }

     protected:
      virtual void UpdateGameLogicDerived() = 0;

      std::shared_ptr<SceneGui> scene_gui_;
   };

   enum class CursorStyles
   {
      Default,
      Hovering,
      Rotating,
      Attack
   };

   class Cursor : public S<Cursor>
   {
     public:
      void ResetStyle();
      auto GetCursorImageName() -> std::string_view;
      auto style()
      {
         return style_;
      }
      void set_style(CursorStyles value)
      {
         style_ = value;
      }

     private:
      CursorStyles style_ = CursorStyles::Default;
   };

   class KbInput : public S<KbInput>
   {
     public:
      void OnKeyPress(SDL_Keycode key);
      void OnKeyRelease(SDL_Keycode key);
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

   // Show MouseButton
#if 1
   // Show MouseActionMngr
#if 1
   // Show MouseAction
#if 1
   class MouseAction
   {
     public:
      std::function<void()> action;
      int z_order = 0;
   };
#endif

   class MouseActionMngr
   {
     public:
      void AddFiredAction(std::function<void()> action, int z_order = 0);
      void AddReleasedAction(std::function<void()> action, int z_order = 0);
      bool ExecFiredActions();
      bool ExecReleasedActions();
      void ClearFiredActions();
      void ClearReleasedActions();

     private:
      std::vector<MouseAction> fired_actions_;
      std::vector<MouseAction> released_actions_;
   };
#endif

   class MouseButton
   {
     public:
      MouseButton()
          : action_mngr_(std::make_shared<MouseActionMngr>())
      {
      }

      void OnPress();
      void OnRelease();
      void ExecMouseActions();
      void AddFiredAction(std::function<void()> action, int z_order = 0);
      void AddReleasedAction(std::function<void()> action, int z_order = 0);
      auto is_pressed()
      {
         return is_pressed_;
      }
      auto action_mngr()
      {
         return action_mngr_;
      }

     private:
      bool is_pressed_ = false;
      bool has_been_fired_ = false;
      bool has_been_released_ = false;
      std::shared_ptr<MouseActionMngr> action_mngr_;
   };
#endif

   class MouseInput : public S<MouseInput>
   {
     public:
      MouseInput()
          : left_btn_(std::make_shared<MouseButton>()),
            right_btn_(std::make_shared<MouseButton>())
      {
      }
      void OnPress(Uint8 button);
      void OnRelease(Uint8 button);
      void ExecMouseActions();
      auto left_btn()
      {
         return left_btn_;
      }
      auto right_btn()
      {
         return right_btn_;
      }

     private:
      std::shared_ptr<MouseButton> left_btn_;
      std::shared_ptr<MouseButton> right_btn_;
   };

   class SDLDeleter
   {
     public:
      void operator()(SDL_Window *win);
      void operator()(SDL_Renderer *rend);
      void operator()(SDL_Surface *surf);
      void operator()(SDL_Texture *tex);
      void operator()(TTF_Font *font);
   };

   class Graphics : public S<Graphics>
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
