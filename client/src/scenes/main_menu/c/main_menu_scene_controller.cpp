#if 1
#include "main_menu_scene_controller.h"
#include "assets/m/model_bank.h"
#include "render-models/v/cmd/new_model.h"
#endif

namespace Narradia
{
   void MainMenuSceneController::OnEnter()
   {
      auto all_models = *ModelBank::get()->models();
      for (auto &entry : all_models)
         NewModel(entry.first);
   }

   void MainMenuSceneController::UpdateGameFlowDerived()
   {
   }
}
