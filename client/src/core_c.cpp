#if 1
#include "core_c.h"
#include "scenes/intro/intro_scene_c.h"
#include "scenes/main/main_scene_c.h"
#include "scenes/main_menu/main_menu_scene_c.h"
#include "scenes/map_overview_gen/map_overview_gen_scene_c.h"
#endif

namespace Narradia
{
   // EngineC
#if 1
   auto EngineC::HandleInput() -> void
   {
      PollEvents();
   }
   auto EngineC::UpdateGameFlow() -> void
   {
      SceneMngrC::get()->UpdateGameFlowCurrScene();
   }
   void EngineC::PollEvents()
   {
      SDL_Event ev;

      while (SDL_PollEvent(&ev) != 0)
      {
         switch (ev.type)
         {
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

   // SceneMngrC
#if 1
   SceneMngrC::SceneMngrC()
   {
      scene_controllers_[SceneNames::Intro] = IntroSceneC::get();
      scene_controllers_[SceneNames::MainMenu] = MainMenuSceneC::get();
      scene_controllers_[SceneNames::MapOverviewGen] = MapOverViewGenSceneC::get();
      scene_controllers_[SceneNames::Main] = MainSceneC::get();
   }
   auto SceneMngrC::UpdateGameFlowCurrScene() -> void
   {
      SceneMngr::get()->set_curr_scene_canceled(false);
      auto curr_scene = SceneMngr::get()->curr_scene();
      if (scene_controllers_.count(curr_scene) != 0)
         scene_controllers_.at(curr_scene)->UpdateGameFlow();
   }
   auto SceneMngrC::ChangeScene(SceneNames new_scene) -> void
   {
      SceneMngr::get()->set_curr_scene(new_scene);
      scene_controllers_.at(new_scene)->OnEnter();
      SceneMngr::get()->set_curr_scene_canceled(true);
   }
#endif

   // ISceneC
#if 1
   auto ISceneC::UpdateGameFlow() -> void
   {
      UpdateGameFlowDerived();
   }
#endif
}
