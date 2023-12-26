#include "world_view_module.h"
#include "camera.h"
#include "core-assets/m/model_bank.h"
namespace Narradia
{
   WorldViewModule::WorldViewModule()
   {
   }

   void WorldViewModule::UpdateGameLogic()
   {
      Camera::get()->UpdateGameLogic();
   }
}
