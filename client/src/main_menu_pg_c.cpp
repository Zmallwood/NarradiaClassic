#if 1
#include "main_menu_pg_c.h"
#include "assets.h"
#include "render-models/cmd_v/new_model.h"
#endif

namespace Narradia
{
   void MainMenuPgC::OnEnter()
   {
      auto all_models = *ModelBank::get()->models();
      for (auto &entry : all_models)
         NewModel(entry.first);
   }
   void MainMenuPgC::UpdateGameFlowDerived()
   {
   }
}
