#if 1
#include "intro_scene_controller.h"
#include "core/m/kb_input.h"
#include "core/m/mouse_input.h"
#include "core/c/scene_mngr_controller.h"
#endif

namespace Narradia
{
   void IntroSceneController::OnEnter()
   {
   }

   void IntroSceneController::UpdateGameFlowDerived()
   {
      if (KbInput::get()->AnyKeyIsPressedPickResult())
      {
         SceneMngrController::get()->ChangeScene(SceneNames::MainMenu);
      }
      MouseInput::get()->left_btn()->AddFiredAction(
          [] { SceneMngrController::get()->ChangeScene(SceneNames::MainMenu); });
      MouseInput::get()->right_btn()->AddFiredAction(
          [] { SceneMngrController::get()->ChangeScene(SceneNames::MainMenu); });
   }
}
