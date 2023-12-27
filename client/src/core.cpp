#if 1
#include "core.h"
#include "gui-core.h"
#include "scenes/intro/intro_scene.h"
#include "scenes/main/main_scene.h"
#include "scenes/main_menu/main_menu_scene.h"
#include "scenes/map_overview_gen/map_overview_gen_scene.h"
#endif

namespace Narradia
{
   // Engine
#if 1
   Engine::Engine()
   {
      srand(time(nullptr));
   }
   void Engine::UpdateGameLogic()
   {
      Cursor::get()->ResetStyle();
      SceneMngr::get()->UpdateGameLogicCurrScene();
      MouseInput::get()->ExecMouseActions();
   }
   void Engine::Finalize()
   {
      SceneMngr::get()->FinalizeCurrScene();
   }
#endif

   // FPSCapper
#if 1
   auto FPSCapper::Below60FPS() -> bool
   {
      auto curr_ticks = SDL_GetTicks();
      auto delta = curr_ticks - prev_ticks_;
      if (delta > 1000 / 60.0f)
      {
         prev_ticks_ = curr_ticks;
         return true;
      }
      return false;
   }
#endif

// SceneMngr
#if 1
   SceneMngr::SceneMngr()
   {
      scenes_[SceneNames::Intro] = IntroScene::get();
      scenes_[SceneNames::MainMenu] = MainMenuScene::get();
      scenes_[SceneNames::MapOverviewGen] = MapOverviewGenScene::get();
      scenes_[SceneNames::Main] = MainScene::get();
      curr_scene_ = SceneNames::Intro;
   }
   void SceneMngr::UpdateGameLogicCurrScene()
   {
      if (curr_scene_canceled_)
         return;
      if (scenes_.count(curr_scene_) != 0)
         scenes_.at(curr_scene_)->UpdateGameLogic();
   }
   void SceneMngr::FinalizeCurrScene()
   {
      if (curr_scene_canceled_)
         return;
      if (scenes_.count(curr_scene_) != 0)
         scenes_.at(curr_scene_)->Finalize();
   }
#endif

   // IScene
#if 1
   IScene::IScene()
       : scene_gui_(std::make_shared<SceneGui>())
   {
   }
   void IScene::UpdateGameLogic()
   {
      UpdateGameLogicDerived();
      scene_gui_->UpdateGameLogic();
   }
#endif

// Cursor
#if 1
   void Cursor::ResetStyle()
   {
      style_ = CursorStyles::Default;
   }
   auto Cursor::GetCursorImageName() -> std::string_view
   {
      std::string_view img_name;

      switch (style_)
      {
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
   void KbInput::OnKeyPress(SDL_Keycode key)
   {
      pressed_keys_.insert(key);
      fired_keys_.insert(key);
   }
   void KbInput::OnKeyRelease(SDL_Keycode key)
   {
      pressed_keys_.erase(key);
   }
   bool KbInput::KeyIsPressed(SDL_Keycode key)
   {
      return pressed_keys_.count(key);
   }
   bool KbInput::KeyHasBeenFiredPickResult(SDL_Keycode key)
   {
      auto result = fired_keys_.count(key) > 0;
      fired_keys_.erase(key);
      return result;
   }
   bool KbInput::AnyKeyIsPressedPickResult()
   {
      auto result = pressed_keys_.size() > 0;
      pressed_keys_.clear();
      return result;
   }
   void KbInput::AppendTextInput(std::string_view to_append)
   {
      text_input_.append(to_append);
   }
   std::string_view KbInput::PickTextInput()
   {
      auto result = text_input_;
      text_input_ = "";
      return result;
   }
#endif

   // MouseInput
#if 1
   void MouseInput::OnPress(Uint8 button)
   {
      switch (button)
      {
      case SDL_BUTTON_LEFT:
         left_btn_->OnPress();
         break;
      case SDL_BUTTON_RIGHT:
         right_btn_->OnPress();
         break;
      }
   }
   void MouseInput::OnRelease(Uint8 button)
   {
      switch (button)
      {
      case SDL_BUTTON_LEFT:
         left_btn_->OnRelease();
         break;
      case SDL_BUTTON_RIGHT:
         right_btn_->OnRelease();
         break;
      }
   }
   void MouseInput::ExecMouseActions()
   {
      left_btn_->ExecMouseActions();
      right_btn_->ExecMouseActions();
   }
#endif

   // MouseButton
#if 1
   void MouseButton::OnPress()
   {
      is_pressed_ = true;
      has_been_fired_ = true;
      has_been_released_ = false;
   }
   void MouseButton::OnRelease()
   {
      is_pressed_ = false;
      has_been_fired_ = false;
      has_been_released_ = true;
   }
   void MouseButton::ExecMouseActions()
   {
      if (has_been_fired_)
      {
         action_mngr_->ExecFiredActions();
      }
      action_mngr_->ClearFiredActions();
      has_been_fired_ = false;
      if (has_been_released_)
      {
         action_mngr_->ExecReleasedActions();
      }
      action_mngr_->ClearReleasedActions();
      has_been_released_ = false;
   }
   void MouseButton::AddFiredAction(std::function<void()> action, int z_order)
   {
      action_mngr_->AddFiredAction(action, z_order);
   }
   void MouseButton::AddReleasedAction(std::function<void()> action, int z_order)
   {
      action_mngr_->AddReleasedAction(action, z_order);
   }
#endif

   // MouseActionMngr
#if 1
   void MouseActionMngr::AddFiredAction(std::function<void()> action, int z_order)
   {
      fired_actions_.push_back({action, z_order});
   }
   void MouseActionMngr::AddReleasedAction(std::function<void()> action, int z_order)
   {
      released_actions_.push_back({action, z_order});
   }
   bool MouseActionMngr::ExecFiredActions()
   {
      if (fired_actions_.size() == 0)
         return false;
      int top_most_z_order = -1;
      std::vector<MouseAction> top_most_actions;
      for (auto action : fired_actions_)
      {
         if (action.z_order > top_most_z_order)
         {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
         else if (action.z_order == top_most_z_order)
         {
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
      }
      for (auto &action : top_most_actions)
         action.action();
      return true;
   }
   bool MouseActionMngr::ExecReleasedActions()
   {
      if (released_actions_.size() == 0)
         return false;
      int top_most_z_order = -1;
      std::vector<MouseAction> top_most_actions;
      for (auto action : released_actions_)
      {
         if (action.z_order > top_most_z_order)
         {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
         else if (action.z_order == top_most_z_order)
         {
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
      }
      for (auto &action : top_most_actions)
         action.action();
      return true;
   }
   void MouseActionMngr::ClearFiredActions()
   {
      fired_actions_.clear();
   }
   void MouseActionMngr::ClearReleasedActions()
   {
      released_actions_.clear();
   }
#endif

   // SDLDeleter
#if 1
   void SDLDeleter::operator()(SDL_Window *win)
   {
      SDL_DestroyWindow(win);
   }
   void SDLDeleter::operator()(SDL_Renderer *rend)
   {
      SDL_DestroyRenderer(rend);
   }
   void SDLDeleter::operator()(SDL_Surface *surf)
   {
      SDL_FreeSurface(surf);
   }
   void SDLDeleter::operator()(SDL_Texture *tex)
   {
      SDL_DestroyTexture(tex);
   }
   void SDLDeleter::operator()(TTF_Font *font)
   {
      TTF_CloseFont(font);
   }
#endif
}
