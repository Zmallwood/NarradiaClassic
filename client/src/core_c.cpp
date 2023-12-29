#if 1
#include "core_c.h"
#include "intro_pg_c.h"
#include "main_pg_c.h"
#include "main_menu_pg_c.h"
#include "map_creation_pg_c.h"
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
      PageMngrC::get()->UpdateGameFlowCurrScene();
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

   // PageMngrC
#if 1
   PageMngrC::PageMngrC()
   {
      scene_controllers_[PageNames::Intro] = IntroPgC::get();
      scene_controllers_[PageNames::MainMenu] = MainMenuPgC::get();
      scene_controllers_[PageNames::MapCreation] = MapCreationPgC::get();
      scene_controllers_[PageNames::Main] = MainPgC::get();
   }
   auto PageMngrC::UpdateGameFlowCurrScene() -> void
   {
      PageMngr::get()->set_curr_scene_canceled(false);
      auto curr_scene = PageMngr::get()->curr_scene();
      if (scene_controllers_.count(curr_scene) != 0)
         scene_controllers_.at(curr_scene)->UpdateGameFlow();
   }
   auto PageMngrC::ChangeScene(PageNames new_scene) -> void
   {
      PageMngr::get()->set_curr_scene(new_scene);
      scene_controllers_.at(new_scene)->OnEnter();
      PageMngr::get()->set_curr_scene_canceled(true);
   }
#endif

   // IPageC
#if 1
   auto IPageC::UpdateGameFlow() -> void
   {
      UpdateGameFlowDerived();
   }
#endif
}
