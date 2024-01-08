#include "Core.h"
#include "GuiCore/GuiCore.h"
#include "GuiMainPg.h"
#include "Pages.h"
#include "Rendering/ImagesRendering.h"
#include "Rendering/TextRendering.h"
#include "Conf/Constants.h"

namespace Narradia {

   // Model

#if 1
   // Engine
#if 1
   Engine::Engine() {
      srand(time(nullptr));
   }

   Engine::~Engine() {
      if (k_verbose)
         std::cout << "Disposing Engine\n";
   }

   void Engine::UpdateGameLogic() {
      try {
         Cursor::get()->ResetStyle();
         PageMngr::get()->UpdateGameLogicCurrScene();
         MouseInput::get()->ExecMouseActions();
      } catch (Exception &e) {
         Console::get()->Print("Exception in Engine::UpdateGameLogic: " + String(e.what()));
      }
   }

   void Engine::Finalize() {
      PageMngr::get()->FinalizeCurrScene();
   }
#endif

   // FPSCapper
#if 1
   bool FPSCapper::Below60FPS() {
      auto curr_ticks = SDL_GetTicks();
      auto delta = curr_ticks - prev_ticks_;

      if (delta > 1000 / 60.0f) {
         prev_ticks_ = curr_ticks;

         return true;
      }

      return false;
   }
#endif

// PageMngr
#if 1
   PageMngr::PageMngr() {
      scenes_[PageNames::Intro] = IntroPg::get();
      scenes_[PageNames::MainMenu] = MainMenuPg::get();
      scenes_[PageNames::MapCreation] = MapCreationPg::get();
      scenes_[PageNames::Main] = MainPg::get();

      curr_scene_ = PageNames::Intro;
   }

   void PageMngr::UpdateGameLogicCurrScene() {
      if (curr_scene_canceled_)
         return;

      if (scenes_.count(curr_scene_) != 0)
         scenes_.at(curr_scene_)->UpdateGameLogic();
   }

   void PageMngr::FinalizeCurrScene() {
      if (curr_scene_canceled_)
         return;

      if (scenes_.count(curr_scene_) != 0)
         scenes_.at(curr_scene_)->Finalize();
   }
#endif

   // IPage
#if 1
   IPage::IPage()
       : scene_gui_(MakeShared<SceneGui>()) {
   }

   void IPage::UpdateGameLogic() {
      UpdateGameLogicDerived();
      scene_gui_->UpdateGameLogic();
   }
#endif

// Cursor
#if 1
   Cursor::~Cursor() {
      if (k_verbose)
         std::cout << "Disposing Cursor.\n";
   }

   void Cursor::ResetStyle() {
      style_ = CursorStyles::Default;
   }

   StringView Cursor::GetCursorImageName() {
      StringView img_name;

      switch (style_) {
      case CursorStyles::Default:
         img_name = "CursorDefault";
         break;

      case CursorStyles::Hovering:
         img_name = "CursorHovering";
         break;

      case CursorStyles::Rotating:
         img_name = "CursorRotating";
         break;

      case CursorStyles::Attack:
         img_name = "CursorAttack";
         break;
      }

      return img_name;
   }
#endif

// KbInput
#if 1
   void KbInput::OnKeyPress(SDL_Keycode key) {
      pressed_keys_.insert(key);
      fired_keys_.insert(key);
   }

   void KbInput::OnKeyRelease(SDL_Keycode key) {
      pressed_keys_.erase(key);
   }

   bool KbInput::KeyIsPressed(SDL_Keycode key) {
      return pressed_keys_.count(key);
   }

   bool KbInput::KeyHasBeenFiredPickResult(SDL_Keycode key) {
      auto result = fired_keys_.count(key) > 0;
      fired_keys_.erase(key);

      return result;
   }

   bool KbInput::AnyKeyIsPressedPickResult() {
      auto result = pressed_keys_.size() > 0;
      pressed_keys_.clear();

      return result;
   }

   void KbInput::AppendTextInput(StringView to_append) {
      text_input_.append(to_append);
   }

   std::string_view KbInput::PickTextInput() {
      auto result = text_input_;
      text_input_ = "";

      return result;
   }
#endif

   // MouseInput
#if 1
   void MouseInput::OnPress(Uint8 button) {
      switch (button) {
      case SDL_BUTTON_LEFT:
         left_btn_->OnPress();
         break;

      case SDL_BUTTON_RIGHT:
         right_btn_->OnPress();
         break;
      }
   }

   void MouseInput::OnRelease(Uint8 button) {
      switch (button) {
      case SDL_BUTTON_LEFT:
         left_btn_->OnRelease();
         break;

      case SDL_BUTTON_RIGHT:
         right_btn_->OnRelease();
         break;
      }
   }

   void MouseInput::ExecMouseActions() {
      left_btn_->ExecMouseActions();
      right_btn_->ExecMouseActions();
   }
#endif

   // MouseButton
#if 1
   void MouseButton::OnPress() {
      is_pressed_ = true;
      has_been_fired_ = true;
      has_been_released_ = false;
   }

   void MouseButton::OnRelease() {
      is_pressed_ = false;
      has_been_fired_ = false;
      has_been_released_ = true;
   }

   void MouseButton::ExecMouseActions() {
      if (has_been_fired_) {
         action_mngr_->ExecFiredActions();
      }

      action_mngr_->ClearFiredActions();
      has_been_fired_ = false;

      if (has_been_released_) {
         action_mngr_->ExecReleasedActions();
      }

      action_mngr_->ClearReleasedActions();
      has_been_released_ = false;
   }

   void MouseButton::AddFiredAction(Function<void()> action, int z_order) {
      action_mngr_->AddFiredAction(action, z_order);
   }

   void MouseButton::AddReleasedAction(Function<void()> action, int z_order) {
      action_mngr_->AddReleasedAction(action, z_order);
   }
#endif

   // MouseActionMngr
#if 1
   void MouseActionMngr::AddFiredAction(Function<void()> action, int z_order) {
      fired_actions_.push_back({action, z_order});
   }

   void MouseActionMngr::AddReleasedAction(Function<void()> action, int z_order) {
      released_actions_.push_back({action, z_order});
   }

   bool MouseActionMngr::ExecFiredActions() {
      if (fired_actions_.size() == 0)
         return false;

      int top_most_z_order = -1;
      Vec<MouseAction> top_most_actions;

      for (auto action : fired_actions_) {
         if (action.z_order > top_most_z_order) {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         } else if (action.z_order == top_most_z_order) {
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
      }

      for (auto &action : top_most_actions)
         action.action();

      return true;
   }

   bool MouseActionMngr::ExecReleasedActions() {
      if (released_actions_.size() == 0)
         return false;

      int top_most_z_order = -1;
      Vec<MouseAction> top_most_actions;

      for (auto action : released_actions_) {
         if (action.z_order > top_most_z_order) {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         } else if (action.z_order == top_most_z_order) {
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
      }

      for (auto &action : top_most_actions)
         action.action();

      return true;
   }

   void MouseActionMngr::ClearFiredActions() {
      fired_actions_.clear();
   }

   void MouseActionMngr::ClearReleasedActions() {
      released_actions_.clear();
   }
#endif

   // SDLDeleter
#if 1
   void SDLDeleter::operator()(SDL_Window *win) {
      SDL_DestroyWindow(win);
   }

   void SDLDeleter::operator()(SDL_Renderer *rend) {
      SDL_DestroyRenderer(rend);
   }

   void SDLDeleter::operator()(SDL_Surface *surf) {
      SDL_FreeSurface(surf);
   }

   void SDLDeleter::operator()(SDL_Texture *tex) {
      SDL_DestroyTexture(tex);
   }

   void SDLDeleter::operator()(TTF_Font *font) {
      TTF_CloseFont(font);
   }
#endif

   // Console
#if 1
   void Console::UpdateGameLogic() {
      if (KbInput::get()->KeyHasBeenFiredPickResult(SDLK_RETURN)) {
         input_active_ = !input_active_;
      }

      if (input_active_) {
         auto new_text_input = KbInput::get()->PickTextInput();
         input_text_.insert(cursor_position_, new_text_input);
         cursor_position_ += new_text_input.length();
      }
   }

   void Console::Print(StringView text, Color text_color) {
      if (!enabled_)
         return;

      auto printed_text =
          String(CurrTime().data()) + "." + ToString(SDL_GetTicks() % 1000) + ") " + text.data();

      text_lines_.push_back({printed_text, text_color});
   }

   std::string Console::InputTextWithCursor() {
      auto res = input_text_;

      if (SDL_GetTicks() % 600 < 300)
         res.insert(cursor_position_, "|");
      else
         res.insert(cursor_position_, " ");

      return res;
   }

   RectF Console::Bounds() {
      return PageMngr::get()->curr_scene() == PageNames::Main
                 ? kDefaultBounds.Translate(0.0f, -ExperienceBar::kBarHeight)
                 : kDefaultBounds;
   }
#endif

   // ConsoleCalc
#if 1
   int ConsoleCalc::MaxNumLines() {
      return static_cast<int>(Console::get()->Bounds().h / Console::kTextLineHeight) - 2;
   }

   int ConsoleCalc::TextLineIndex(int visible_row_index) {
      return static_cast<int>(Console::get()->text_lines().size()) - MaxNumLines() +
             visible_row_index;
   }

   PointF ConsoleCalc::InputTextPosition() {
      return InputArrowRect().GetPosition().Translate(
          Console::kTextLineHeight, Console::kTextLineHeight / 2);
   }

   PointF ConsoleCalc::TextLinePosition(int visible_row_index) {
      return {
          Console::get()->Bounds().x + 0.01f,
          Console::get()->Bounds().y + (visible_row_index + 1) * Console::kTextLineHeight};
   }

   RectF ConsoleCalc::HorizontalSplitterRect() {
      return {
          Console::get()->Bounds().x,
          Console::get()->Bounds().y + Console::get()->Bounds().h - 1.3f * Console::kTextLineHeight,
          Console::get()->Bounds().w, Console::kSplitLineHeight};
   }

   RectF ConsoleCalc::InputArrowRect() {
      return {
          0.0f,
          Console::get()->Bounds().y + Console::get()->Bounds().h - 1.3f * Console::kTextLineHeight,
          Console::kTextLineHeight, Console::kTextLineHeight};
   }
#endif
#endif

   // View

#if 1
// EngineV
#if 1
   EngineV::~EngineV() {
      if (k_verbose)
         std::cout << "Disposing EngineV\n";
   }

   void EngineV::Render() {
      try {
         GraphicsV::get()->ClearCanvas();
         PageMngrV::get()->RenderCurrScene();
         ConsoleV::get()->Render();
         CursorV::get()->RenderCursor();
         GraphicsV::get()->PresentCanvas();
      } catch (std::exception &e) {
         Console::get()->Print("Exception in EngineV::Render:" + std::string(e.what()));
      }
   };
#endif

      // PageMngrV
#if 1
   PageMngrV::PageMngrV() {
      scene_views_[PageNames::Intro] = IntroPgV::get();
      scene_views_[PageNames::MainMenu] = MainMenuPgV::get();
      scene_views_[PageNames::MapCreation] = MapCreationPgV::get();
      scene_views_[PageNames::Main] = MainPgV::get();
   }

   void PageMngrV::RenderCurrScene() {
      if (PageMngr::get()->curr_scene_canceled())
         return;

      auto curr_scene = PageMngr::get()->curr_scene();

      if (scene_views_.count(curr_scene) != 0)
         scene_views_.at(curr_scene)->Render();
   }
#endif

   // IPageV
#if 1
   IPageV::IPageV()
       : scene_gui_view_(MakeShared<SceneGuiV>()) {
   }

   void IPageV::Render() {
      RenderDerived();
      scene_gui_view_->Render();
   }
#endif

// CursorV
#if 1
   CursorV::CursorV() {
      SDL_ShowCursor(0);

      rid_image = NewImage();
   }

   void CursorV::RenderCursor() {
      auto mouse_pos = MousePos();
      auto w = kCursorWidth;
      auto h = w * AspectRatio();
      RectF rect = {mouse_pos.x - w, mouse_pos.y - h, w * 2, h * 2};
      auto image_name = Cursor::get()->GetCursorImageName();

      DrawImage(image_name, rid_image, rect);
   }
#endif

   // GraphicsV
#if 1
   GraphicsV::GraphicsV() {
      auto win_size = Graphics::get()->win_size();
      auto win_flags = Graphics::get()->win_flags();
      auto win = SharedPtr<SDL_Window>(
          SDL_CreateWindow(Engine::get()->title().data(), 0, 0, win_size.w, win_size.h, win_flags),
          SDLDeleter());

      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

      if (SDL_GL_CreateContext(win.get()) == nullptr) {
         std::cout << "OpenGL context could not be "
                      "created! SDL Error: "
                   << String(SDL_GetError()) << std::endl;
         return;
      }

      Graphics::get()->set_win(win);

      InitGL();
   }

   void GraphicsV::ClearCanvas() {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }

   void GraphicsV::PresentCanvas() {
      SDL_GL_SwapWindow(Graphics::get()->win().get());
   }

   void GraphicsV::InitGL() {
      glewExperimental = GL_TRUE;
      auto glew_error = glewInit();

      if (glew_error != GLEW_OK)
         std::cout << "Error initializing GLEW: " << glewGetErrorString(glew_error) << std::endl;

      if (SDL_GL_SetSwapInterval(0) < 0)
         std::cout << "Warning: Unable to disable VSync, SDL Error: " << SDL_GetError()
                   << std::endl;

      glClearColor(k_clearColor.r, k_clearColor.g, k_clearColor.b, k_clearColor.a);

      if (kCullFace) {
         glEnable(GL_CULL_FACE);
         glCullFace(GL_FRONT);
      }

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   }
#endif

   // ConsoleV
#if 1
   ConsoleV::ConsoleV() {
      rid_image_ = NewImage();
      rid_split_line_ = NewImage();
      rid_cmd_line_input_arrow_ = NewImage();
      rid_input_text_ = NewString();

      for (auto i = 0; i < ConsoleCalc::get()->MaxNumLines(); i++)
         rids_text_lines_.push_back(NewString());
   }

   void ConsoleV::Render() const {
      auto model = Console::get();

      if (!model->enabled())
         return;

      DrawImage("TextOutBoxBack", rid_image_, Console::get()->Bounds());

      for (auto i = 0; i < ConsoleCalc::get()->MaxNumLines(); i++) {
         auto text_line_index = ConsoleCalc::get()->TextLineIndex(i);

         if (text_line_index >= 0) {
            PointF position = ConsoleCalc::get()->TextLinePosition(i);

            DrawString(
                rids_text_lines_.at(i), model->text_lines().at(text_line_index).text, position,
                model->text_lines().at(text_line_index).color);
         }
      }

      DrawImage("Wheat", rid_split_line_, ConsoleCalc::get()->HorizontalSplitterRect());

      if (!model->input_active())
         return;

      DrawImage(
          "CommandLineInputArrow", rid_cmd_line_input_arrow_, ConsoleCalc::get()->InputArrowRect());

      DrawString(
          rid_input_text_, model->InputTextWithCursor(), ConsoleCalc::get()->InputTextPosition());
   }
#endif
#endif

   // Controller

#if 1
   // EngineC
#if 1
   void EngineC::HandleInput() {
      PollEvents();
   }

   void EngineC::UpdateGameFlow() {
      PageMngrC::get()->UpdateGameFlowCurrScene();
   }

   void EngineC::PollEvents() {
      SDL_Event ev;

      while (SDL_PollEvent(&ev) != 0) {
         switch (ev.type) {
         case SDL_QUIT:
            Engine::get()->set_running(false);
            break;

         case SDL_KEYDOWN:
            KbInput::get()->OnKeyPress(ev.key.keysym.sym);
            break;

         case SDL_KEYUP:
            KbInput::get()->OnKeyRelease(ev.key.keysym.sym);
            break;

         case SDL_MOUSEBUTTONDOWN:
            MouseInput::get()->OnPress(ev.button.button);
            break;

         case SDL_MOUSEBUTTONUP:
            MouseInput::get()->OnRelease(ev.button.button);
            break;

         case SDL_MOUSEMOTION:
            break;

         case SDL_TEXTINPUT:
            KbInput::get()->AppendTextInput(ev.text.text);
            break;

         case SDL_MOUSEWHEEL:
            break;
         }
      }
   }
#endif

   // PageMngrC
#if 1
   PageMngrC::PageMngrC() {
      scene_controllers_[PageNames::Intro] = IntroPgC::get();
      scene_controllers_[PageNames::MainMenu] = MainMenuPgC::get();
      scene_controllers_[PageNames::MapCreation] = MapCreationPgC::get();
      scene_controllers_[PageNames::Main] = MainPgC::get();
   }

   void PageMngrC::UpdateGameFlowCurrScene() {
      PageMngr::get()->set_curr_scene_canceled(false);
      auto curr_scene = PageMngr::get()->curr_scene();

      if (scene_controllers_.count(curr_scene) != 0)
         scene_controllers_.at(curr_scene)->UpdateGameFlow();
   }

   void PageMngrC::ChangeScene(PageNames new_scene) {
      PageMngr::get()->set_curr_scene(new_scene);
      scene_controllers_.at(new_scene)->OnEnter();
      PageMngr::get()->set_curr_scene_canceled(true);
   }
#endif

   // IPageC
#if 1
   void IPageC::UpdateGameFlow() {
      UpdateGameFlowDerived();
   }
#endif
#endif

}
