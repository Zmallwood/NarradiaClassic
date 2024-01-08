#pragma once

namespace Narradia {

   // Model

#if 1
   class Engine : public Singleton<Engine> {
     public:
      Engine();
      ~Engine();
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
      StringView title_ = "Narradia";
   };

   class FPSCapper : public Singleton<FPSCapper> {
     public:
      bool Below60FPS();

     private:
      int prev_ticks_ = 0;
   };

   enum class PageNames { None, Intro, MainMenu, Main, MapCreation };

   class IPage;

   class PageMngr : public Singleton<PageMngr> {
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
      Map<PageNames, SharedPtr<IPage>> scenes_;
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

      SharedPtr<SceneGui> scene_gui_;
   };

   enum class CursorStyles { Default, Hovering, Rotating, Attack };

   class Cursor : public Singleton<Cursor> {
     public:
      ~Cursor();
      void ResetStyle();
      StringView GetCursorImageName();

      auto style() {
         return style_;
      }

      void set_style(CursorStyles value) {
         style_ = value;
      }

     private:
      CursorStyles style_ = CursorStyles::Default;
   };

   class KbInput : public Singleton<KbInput> {
     public:
      void OnKeyPress(SDL_Keycode key);
      void OnKeyRelease(SDL_Keycode key);
      bool KeyIsPressed(SDL_Keycode key);
      bool KeyHasBeenFiredPickResult(SDL_Keycode key);
      bool AnyKeyIsPressedPickResult();
      void AppendTextInput(StringView to_append);
      StringView PickTextInput();

     private:
      Set<SDL_Keycode> pressed_keys_;
      Set<SDL_Keycode> fired_keys_;
      String text_input_;
   };

   // Show MouseButton
#if 1
   // Show MouseActionMngr
#if 1
   // Show MouseAction
#if 1
   class MouseAction {
     public:
      Function<void()> action;
      int z_order = 0;
   };
#endif

   class MouseActionMngr {
     public:
      void AddFiredAction(Function<void()> action, int z_order = 0);
      void AddReleasedAction(Function<void()> action, int z_order = 0);
      bool ExecFiredActions();
      bool ExecReleasedActions();
      void ClearFiredActions();
      void ClearReleasedActions();

     private:
      Vec<MouseAction> fired_actions_;
      Vec<MouseAction> released_actions_;
   };
#endif

   class MouseButton {
     public:
      MouseButton()
          : action_mngr_(MakeShared<MouseActionMngr>()) {
      }

      void OnPress();
      void OnRelease();
      void ExecMouseActions();
      void AddFiredAction(Function<void()> action, int z_order = 0);
      void AddReleasedAction(Function<void()> action, int z_order = 0);

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
      SharedPtr<MouseActionMngr> action_mngr_;
   };
#endif

   class MouseInput : public Singleton<MouseInput> {
     public:
      MouseInput()
          : left_btn_(MakeShared<MouseButton>()),
            right_btn_(MakeShared<MouseButton>()) {
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
      SharedPtr<MouseButton> left_btn_;
      SharedPtr<MouseButton> right_btn_;
   };

   class SDLDeleter {
     public:
      void operator()(SDL_Window *win);
      void operator()(SDL_Renderer *rend);
      void operator()(SDL_Surface *surf);
      void operator()(SDL_Texture *tex);
      void operator()(TTF_Font *font);
   };

   class Graphics : public Singleton<Graphics> {
     public:
      auto win() {
         return win_;
      }

      void set_win(SharedPtr<SDL_Window> value) {
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
      SharedPtr<SDL_Window> win_;
      Size win_size_ = {660, 660};
      Uint32 win_flags_ = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
      Color clear_color_ = {0, 150, 255, 255};
   };

   // Show Console sub classes
#if 1
   class TextLine {
     public:
      String text;
      Color color;
   };
#endif

   class Console : public Singleton<Console> {
     public:
      void UpdateGameLogic();
      void Print(StringView text, Color text_color = Colors::wheat);
      String InputTextWithCursor();
      RectF Bounds();

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
      static constexpr RectF kDefaultBounds = {0.35f, 0.8f, 0.3f, 0.2f};

      Vec<TextLine> text_lines_;
      bool enabled_ = true;
      bool input_active_ = false;
      int cursor_position_ = 0;
      String input_text_;
   };

   class ConsoleCalc : public Singleton<ConsoleCalc> {
     public:
      int MaxNumLines();
      int TextLineIndex(int visible_row_index);
      PointF TextLinePosition(int visible_row_index);
      RectF HorizontalSplitterRect();
      RectF InputArrowRect();
      PointF InputTextPosition();
   };
#endif

   // View

#if 1
   class EngineV : public Singleton<EngineV> {
     public:
      ~EngineV();
      void Render();
   };

   class IPageV;

   class PageMngrV : public Singleton<PageMngrV> {
     public:
      PageMngrV();
      void RenderCurrScene();

     private:
      Map<PageNames, SharedPtr<IPageV>> scene_views_;
   };

   class SceneGuiView;

   class IPageV {
     public:
      IPageV();
      void Render();

     protected:
      virtual void RenderDerived() = 0;

      SharedPtr<SceneGuiView> scene_gui_view_;
   };

   class CursorV : public Singleton<CursorV> {
     public:
      CursorV();
      void RenderCursor();

     private:
      RenderID rid_image;

      static constexpr float kCursorWidth = 0.02f;
   };

   class GraphicsV : public Singleton<GraphicsV> {
     public:
      GraphicsV();
      void ClearCanvas();
      void PresentCanvas();

     private:
      void InitGL();

      static constexpr bool kCullFace = false;
   };

   class ConsoleV : public Singleton<ConsoleV> {
     public:
      ConsoleV();
      void Render() const;

     private:
      RenderID rid_image_;
      RenderID rid_split_line_;
      RenderID rid_cmd_line_input_arrow_;
      RenderID rid_input_text_;
      Vec<RenderID> rids_text_lines_;
   };
#endif

   // Controller

#if 1
   class EngineC : public Singleton<EngineC> {
     public:
      void HandleInput();
      void UpdateGameFlow();

     private:
      void PollEvents();
   };

   class IPageC;

   class PageMngrC : public Singleton<PageMngrC> {
     public:
      PageMngrC();
      void UpdateGameFlowCurrScene();
      void ChangeScene(PageNames new_scene);

     private:
      Map<PageNames, SharedPtr<IPageC>> scene_controllers_;
   };

   class IPageC {
     public:
      virtual void OnEnter() = 0;
      void UpdateGameFlow();

     protected:
      virtual void UpdateGameFlowDerived() = 0;
   };
#endif

}
