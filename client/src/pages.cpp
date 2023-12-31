#if 1
#include "pages.h"
#include "actors.h"
#include "assets.h"
#include "core.h"
#include "core_c.h"
#include "core_v.h"
#include "gui-core.h"
#include "adds-menu_models.h"
#include "adds-non-visual.h"
#include "adds-visual.h"
#include "adds-world_view.h"
#include "gui_comps.h"
#include "gui_windows.h"
#include "rend_models_v.h"
#include "rend_2d_images_v.h"
#include "rend_tiles_v.h"
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
         KeyboardMovementAdd::get()->UpdateGameLogic();
         MouseMovementAdd::get()->UpdateGameLogic();
         WorldViewAdd::get()->UpdateGameLogic();
         MouseRotationAdd::get()->UpdateGameLogic();
         TileHoveringAdd::get()->UpdateGameLogic();
         SkillPerformingAdd::get()->UpdateGameLogic();
         FPSCounterAdd::get()->UpdateGameLogic();
      }
      catch (std::exception &e) {
         Console::get()->Print(
             "Exception in MainPg::UpdateGameLogicDerived: " + std::string(e.what()));
      }
   }
#endif
}
