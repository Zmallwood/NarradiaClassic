#include "main_menu_scene_controller.h"
#include "core-assets/m/model_bank.h"
#include "core-render-models/v/cmd/new_model.h"
namespace Narradia
{
   /**
    On entering scene.
   */
   void MainMenuSceneController::OnEnter()
   {
      auto all_models = *ModelBank::get()->models();
      for (auto &entry : all_models)
         NewModel(entry.first);
   }

   /**
    Update game flow between scenes.
   */
   void MainMenuSceneController::UpdateGameFlowDerived()
   {
   }
}
