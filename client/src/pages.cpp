#if 1
#include "pages.h"
#include "actors.h"
#include "assets.h"
#include "core.h"
#include "core_c.h"
#include "core_v.h"
#include "gui-core.h"
#include "main_menu_pg-adds-menu_models.h"
#include "main_pg-adds-non-visual.h"
#include "main_pg-adds-visual.h"
#include "main_pg-adds-world_view.h"
#include "main_pg-gui_comps.h"
#include "main_pg-gui_windows.h"
#include "render-models/renderer_models_v.h"
#include "render/renderer_2d_images_v.h"
#include "render/renderer_tiles_v.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   // IntroPg
#if 1
   void IntroPg::UpdateGameLogicDerived() {
   }
#endif

   // MainMenuPg
#if 1
   MainMenuPg::MainMenuPg() {
      scene_gui()->AddGuiComponent(
          std::make_shared<GuiButton>("Play", RectF{0.4f, 0.4f, 0.2f, 0.1f}, [] {
             PageMngrC::get()->ChangeScene(PageNames::MapCreation);
          }));
      scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
          "Exit", RectF{0.4f, 0.55f, 0.2f, 0.1f}, [] { Engine::get()->set_running(false); }));
   }
   void MainMenuPg::UpdateGameLogicDerived() {
      MenuModelsAdd::get()->UpdateGameLogic();
   }
#endif

   // MapCreationPg
#if 1
   void MapCreationPg::UpdateGameLogicDerived() {
      WorldViewAdd::get()->UpdateGameLogic();
   }
   void MapCreationPg::Finalize() {
      PageMngrC::get()->ChangeScene(PageNames::Main);
   }
#endif

   // MainPg
#if 1
   MainPg::MainPg() {
      scene_gui()->AddGuiComponent(std::make_shared<ExperienceBar>());
      scene_gui()->AddGuiComponent(std::make_shared<StatusPanel>());
      scene_gui()->AddGuiComponent(GuiWindowWorldMap::get());
   }
   void MainPg::UpdateGameLogicDerived() {
      try {
         KbBindingsAdd::get()->UpdateGameLogic();
         MobMovementAdd::get()->UpdateGameLogic();
         KeyboardMovementAdd::get()->UpdateGameLogic();
         MouseMovementAdd::get()->UpdateGameLogic();
         CombatChaseMovementAdd::get()->UpdateGameLogic();
         WorldViewAdd::get()->UpdateGameLogic();
         MouseRotationAdd::get()->UpdateGameLogic();
         TileHoveringAdd::get()->UpdateGameLogic();
         MobTargetingAdd::get()->UpdateGameLogic();
         CombatAdd::get()->UpdateGameLogic();
         SkillPerformingAdd::get()->UpdateGameLogic();
         MobDeathHandlingAdd::get()->UpdateGameLogic();
         FPSCounterAdd::get()->UpdateGameLogic();
      }
      catch (std::exception &e) {
         Console::get()->Print(
             "Exception in MainPg::UpdateGameLogicDerived: " + std::string(e.what()));
      }
   }
#endif
}
