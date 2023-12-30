#if 1
#include "pages_c.h"
#include "core.h"
#include "core_c.h"
#include "assets.h"
#include "rend_models_v.h"
#include "actors.h"
#include "world-struct.h"
#include "main_pg-adds-non-visual.h"
#endif

namespace Narradia
{
   // IntroPgC
#if 1
   void IntroPgC::OnEnter() {
   }
   void IntroPgC::UpdateGameFlowDerived() {
      if (KbInput::get()->AnyKeyIsPressedPickResult()) {
         PageMngrC::get()->ChangeScene(PageNames::MainMenu);
      }
      MouseInput::get()->left_btn()->AddFiredAction(
          [] { PageMngrC::get()->ChangeScene(PageNames::MainMenu); });
      MouseInput::get()->right_btn()->AddFiredAction(
          [] { PageMngrC::get()->ChangeScene(PageNames::MainMenu); });
   }
#endif
   
   // MainMenuPgC
#if 1
   void MainMenuPgC::OnEnter() {
      auto all_models = *ModelBank::get()->models();
      for (auto &entry : all_models)
         NewModel(entry.first);
   }
   void MainMenuPgC::UpdateGameFlowDerived() {
   }
#endif

   // MapCreationPgC
#if 1
   void MapCreationPgC::OnEnter() {
      auto map_area = World::get()->CurrWorldArea();
      auto x = map_area->GetWidth() / 2.0f;
      auto y = map_area->GetHeight() / 2.0f;
      Player::get()->set_position({x, 0.0f, y});
   }
   void MapCreationPgC::UpdateGameFlowDerived() {
   }
#endif

   // MainPgC
#if 1
   void MainPgC::OnEnter() {
      Console::get()->Print("Entering Narradia");
      PlayerSpawnPositioningAdd::get()->SpawnAtGoodLocation();
   }
   void MainPgC::UpdateGameFlowDerived() {
   }
#endif
}

