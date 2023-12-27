#if 1
#include "kb_bindings_module.h"
#include "core/m/kb_input.h"
#include "main_scene-gui/m/gui_window_world_map.h"
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
