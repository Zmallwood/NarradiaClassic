#if 1
#include "core.h"
#include "conf.h"
#include "gui-core.h"
#include "main_pg-gui_comps.h"
#include "pages.h"
#endif

namespace Narradia
{
   // Engine
#if 1
   Engine::Engine() {
      srand(time(nullptr));
   }
   Engine::~Engine() {
      if (kVerbose)
         std::cout << "Disposing Engine\n";
   }
   void Engine::UpdateGameLogic() {
      try {
         Cursor::get()->ResetStyle();
         PageMngr::get()->UpdateGameLogicCurrScene();
         MouseInput::get()->ExecMouseActions();
      }
      catch (std::exception &e) {
         Console::get()->Print("Exception in Engine::UpdateGameLogic: " + std::string(e.what()));
      }
   }
   void Engine::Finalize() {
      PageMngr::get()->FinalizeCurrScene();
   }
#endif

   // FPSCapper
#if 1
   auto FPSCapper::Below60FPS() -> bool {
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
       : scene_gui_(std::make_shared<SceneGui>()) {
   }
   void IPage::UpdateGameLogic() {
      UpdateGameLogicDerived();
      scene_gui_->UpdateGameLogic();
   }
#endif

// Cursor
#if 1
   Cursor::~Cursor() {
      if (kVerbose)
         std::cout << "Disposing Cursor.\n";
   }
   void Cursor::ResetStyle() {
      style_ = CursorStyles::Default;
   }
   auto Cursor::GetCursorImageName() -> std::string_view {
      std::string_view img_name;

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
   void KbInput::AppendTextInput(std::string_view to_append) {
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
   void MouseButton::AddFiredAction(std::function<void()> action, int z_order) {
      action_mngr_->AddFiredAction(action, z_order);
   }
   void MouseButton::AddReleasedAction(std::function<void()> action, int z_order) {
      action_mngr_->AddReleasedAction(action, z_order);
   }
#endif

   // MouseActionMngr
#if 1
   void MouseActionMngr::AddFiredAction(std::function<void()> action, int z_order) {
      fired_actions_.push_back({action, z_order});
   }
   void MouseActionMngr::AddReleasedAction(std::function<void()> action, int z_order) {
      released_actions_.push_back({action, z_order});
   }
   bool MouseActionMngr::ExecFiredActions() {
      if (fired_actions_.size() == 0)
         return false;
      int top_most_z_order = -1;
      std::vector<MouseAction> top_most_actions;
      for (auto action : fired_actions_) {
         if (action.z_order > top_most_z_order) {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
         else if (action.z_order == top_most_z_order) {
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
      std::vector<MouseAction> top_most_actions;
      for (auto action : released_actions_) {
         if (action.z_order > top_most_z_order) {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
         else if (action.z_order == top_most_z_order) {
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
   auto Console::UpdateGameLogic() -> void {
      if (KbInput::get()->KeyHasBeenFiredPickResult(SDLK_RETURN)) {
         input_active_ = !input_active_;
      }
      if (input_active_) {
         auto new_text_input = KbInput::get()->PickTextInput();
         input_text_.insert(cursor_position_, new_text_input);
         cursor_position_ += new_text_input.length();
      }
   }
   auto Console::Print(std::string_view text, Color text_color) -> void {
      if (!enabled_)
         return;
      auto printed_text = std::string(CurrTime().data()) + "." +
                          std::to_string(SDL_GetTicks() % 1000) + ") " + text.data();
      text_lines_.push_back({printed_text, text_color});
   }
   auto Console::InputTextWithCursor() -> std::string {
      auto res = input_text_;
      if (SDL_GetTicks() % 600 < 300)
         res.insert(cursor_position_, "|");
      else
         res.insert(cursor_position_, " ");
      return res;
   }
   auto Console::Bounds() -> RectF {
      return PageMngr::get()->curr_scene() == PageNames::Main
                 ? kDefaultBounds.Translate(0.0f, -ExperienceBar::kBarHeight)
                 : kDefaultBounds;
   }
#endif

   // ConsoleCalc
#if 1
   auto ConsoleCalc::MaxNumLines() -> int {
      return static_cast<int>(Console::get()->Bounds().h / Console::kTextLineHeight) - 2;
   }
   auto ConsoleCalc::TextLineIndex(int visible_row_index) -> int {
      return static_cast<int>(Console::get()->text_lines().size()) - MaxNumLines() +
             visible_row_index;
   }
   auto ConsoleCalc::InputTextPosition() -> PointF {
      return InputArrowRect().GetPosition().Translate(
          Console::kTextLineHeight, Console::kTextLineHeight / 2);
   }
   auto ConsoleCalc::TextLinePosition(int visible_row_index) -> PointF {
      return {
          Console::get()->Bounds().x + 0.01f,
          Console::get()->Bounds().y + (visible_row_index + 1) * Console::kTextLineHeight};
   }
   auto ConsoleCalc::HorizontalSplitterRect() -> RectF {
      return {
          0.0f,
          Console::get()->Bounds().y + Console::get()->Bounds().h - 1.3f * Console::kTextLineHeight,
          Console::get()->Bounds().w, Console::kSplitLineHeight};
   }
   auto ConsoleCalc::InputArrowRect() -> RectF {
      return {
          0.0f,
          Console::get()->Bounds().y + Console::get()->Bounds().h - 1.3f * Console::kTextLineHeight,
          Console::kTextLineHeight, Console::kTextLineHeight};
   }
#endif
}
