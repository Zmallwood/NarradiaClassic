#if 1
#include "main_menu_pg.h"
#include "core_c.h"
#include "core.h"
#include "main_menu_pg-adds-menu_models.h"
#include "gui-core.h"
#endif

namespace Narradia
{
   MainMenuPg::MainMenuPg()
   {
      scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
          "Play", RectF{0.4f, 0.4f, 0.2f, 0.1f},
          [] { PageMngrC::get()->ChangeScene(PageNames::MapCreation); }));
      scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
          "Exit", RectF{0.4f, 0.55f, 0.2f, 0.1f}, [] { Engine::get()->set_running(false); }));
   }
   void MainMenuPg::UpdateGameLogicDerived()
   {
      MenuModelsAdd::get()->UpdateGameLogic();
   }
}
