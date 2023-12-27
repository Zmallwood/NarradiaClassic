#if 1
#include "intro_scene_c.h"
#include "core/kb_input.h"
#include "core/mouse_input.h"
#include "core/scene_mngr_c.h"
#endif

namespace Narradia
{
   void IntroSceneC::OnEnter()
   {
   }
   void IntroSceneC::UpdateGameFlowDerived()
   {
      if (KbInput::get()->AnyKeyIsPressedPickResult())
      {
         SceneMngrC::get()->ChangeScene(SceneNames::MainMenu);
      }
      MouseInput::get()->left_btn()->AddFiredAction(
          [] { SceneMngrC::get()->ChangeScene(SceneNames::MainMenu); });
      MouseInput::get()->right_btn()->AddFiredAction(
          [] { SceneMngrC::get()->ChangeScene(SceneNames::MainMenu); });
   }
}
