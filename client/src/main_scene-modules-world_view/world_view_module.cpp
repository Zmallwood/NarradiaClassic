#if 1
#include "world_view_module.h"
#include "camera.h"
#include "assets.h"
#endif

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