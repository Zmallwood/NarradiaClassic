#if 1
#include "intro_scene_c.h"
#include "core.h"
#include "core_c.h"
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
