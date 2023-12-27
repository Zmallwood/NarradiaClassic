#if 1
#include "kb_bindings_module.h"
#include "core.h"
#include "main_scene-gui/gui_window_world_map.h"
#endif

namespace Narradia
{
   void KbBindingsModule::UpdateGameLogic()
   {
      if (KbInput::get()->KeyHasBeenFiredPickResult(SDLK_m))
      {
         GuiWindowWorldMap::get()->ToggleVisibility();
      }
   }
}
