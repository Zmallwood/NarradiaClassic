#if 1
#include "intro_pg_c.h"
#include "core.h"
#include "core_c.h"
#endif

namespace Narradia
{
   void IntroPgC::OnEnter()
   {
   }
   void IntroPgC::UpdateGameFlowDerived()
   {
      if (KbInput::get()->AnyKeyIsPressedPickResult())
      {
         PageMngrC::get()->ChangeScene(PageNames::MainMenu);
      }
      MouseInput::get()->left_btn()->AddFiredAction(
          [] { PageMngrC::get()->ChangeScene(PageNames::MainMenu); });
      MouseInput::get()->right_btn()->AddFiredAction(
          [] { PageMngrC::get()->ChangeScene(PageNames::MainMenu); });
   }
}
