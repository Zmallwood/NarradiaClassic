#pragma once

namespace Narradia
{
   class Engine : public S<Engine> {
     public:
      Engine();
      void UpdateGameLogic();
      void Finalize();
      auto is_running() {
         return is_running_;
      }
      void set_running(bool value) {
         is_running_ = value;
      }
      auto title() {
         return title_;
      }

     private:
      bool is_running_ = true;
      std::string_view title_ = "Narradia";
   };

   class FPSCapper : public S<FPSCapper> {
     public:
      auto Below60FPS() -> bool;

     private:
      int prev_ticks_ = 0;
   };

   enum class PageNames { None, Intro, MainMenu, Main, MapCreation };

   class IPage;

   class PageMngr : public S<PageMngr> {
     public:
      PageMngr();
      void UpdateGameLogicCurrScene();
      void FinalizeCurrScene();
      auto curr_scene() {
         return curr_scene_;
      }
      void set_curr_scene(PageNames value) {
         curr_scene_ = value;
      }
      auto curr_scene_canceled() {
         return curr_scene_canceled_;
      }
      void set_curr_scene_canceled(bool value) {
         curr_scene_canceled_ = value;
      }

     private:
      std::map<PageNames, std::shared_ptr<IPage>> scenes_;
      PageNames curr_scene_ = PageNames::None;
      bool curr_scene_canceled_ = false;
   };

   class SceneGui;

   class IPage {
     public:
      IPage();
      void UpdateGameLogic();
      virtual void Finalize() = 0;
      auto scene_gui() {
         return scene_gui_;
      }

     protected:
      virtual void UpdateGameLogicDerived() = 0;

      std::shared_ptr<SceneGui> scene_gui_;
   };

   enum class CursorStyles { Default, Hovering, Rotating, Attack };

   class Cursor : public S<Cursor> {
     public:
      void ResetStyle();
      auto GetCursorImageName() -> std::string_view;
      auto style() {
         return style_;
      }
      void set_style(CursorStyles value) {
         style_ = value;
      }

     private:
      CursorStyles style_ = CursorStyles::Default;
   };

   class KbInput : public S<KbInput> {
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
   class MouseAction {
     public:
      std::function<void()> action;
      int z_order = 0;
   };
#endif

   class MouseActionMngr {
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

   class MouseButton {
     public:
      MouseButton()
          : action_mngr_(std::make_shared<MouseActionMngr>()) {
      }

      void OnPress();
      void OnRelease();
      void ExecMouseActions();
      void AddFiredAction(std::function<void()> action, int z_order = 0);
      void AddReleasedAction(std::function<void()> action, int z_order = 0);
      auto is_pressed() {
         return is_pressed_;
      }
      auto action_mngr() {
         return action_mngr_;
      }

     private:
      bool is_pressed_ = false;
      bool has_been_fired_ = false;
      bool has_been_released_ = false;
      std::shared_ptr<MouseActionMngr> action_mngr_;
   };
#endif

   class MouseInput : public S<MouseInput> {
     public:
      MouseInput()
          : left_btn_(std::make_shared<MouseButton>()),
            right_btn_(std::make_shared<MouseButton>()) {
      }
      void OnPress(Uint8 button);
      void OnRelease(Uint8 button);
      void ExecMouseActions();
      auto left_btn() {
         return left_btn_;
      }
      auto right_btn() {
         return right_btn_;
      }

     private:
      std::shared_ptr<MouseButton> left_btn_;
      std::shared_ptr<MouseButton> right_btn_;
   };

   class SDLDeleter {
     public:
      void operator()(SDL_Window *win);
      void operator()(SDL_Renderer *rend);
      void operator()(SDL_Surface *surf);
      void operator()(SDL_Texture *tex);
      void operator()(TTF_Font *font);
   };

   class Graphics : public S<Graphics> {
     public:
      auto win() {
         return win_;
      }
      void set_win(std::shared_ptr<SDL_Window> value) {
         win_ = value;
      }
      auto win_size() {
         return win_size_;
      }
      auto win_flags() {
         return win_flags_;
      }
      auto clear_color() {
         return clear_color_;
      }

     private:
      std::shared_ptr<SDL_Window> win_;
      Size win_size_ = {660, 660};
      Uint32 win_flags_ = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
      Color clear_color_ = {0, 150, 255, 255};
   };

   // Show Console sub classes
#if 1
   class TextLine {
     public:
      std::string text;
      Color color;
   };
#endif

   class Console : public S<Console> {
     public:
      auto UpdateGameLogic() -> void;
      auto Print(std::string_view text, Color text_color = Colors::wheat) -> void;
      auto InputTextWithCursor() -> std::string;
      auto Bounds() -> RectF;
      auto text_lines() {
         return text_lines_;
      }
      auto enabled() {
         return enabled_;
      }
      auto input_active() {
         return input_active_;
      }
      auto cursor_position() {
         return cursor_position_;
      }
      auto input_text() {
         return input_text_;
      }

      static constexpr float kTextLineHeight = 0.02f;
      static constexpr float kSplitLineHeight = 0.001f;

     private:
      static constexpr RectF kDefaultBounds = {0.0f, 0.8f, 0.3f, 0.2f};

      std::vector<TextLine> text_lines_;
      bool enabled_ = true;
      bool input_active_ = false;
      int cursor_position_ = 0;
      std::string input_text_;
   };

   class ConsoleCalc : public S<ConsoleCalc> {
     public:
      auto MaxNumLines() -> int;
      auto TextLineIndex(int visible_row_index) -> int;
      auto TextLinePosition(int visible_row_index) -> PointF;
      auto HorizontalSplitterRect() -> RectF;
      auto InputArrowRect() -> RectF;
      auto InputTextPosition() -> PointF;
   };
}
