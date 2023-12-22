#include "kb_bindings_module.h"
#include "../../core-input/model/kb_input.h"
#include "../../main_scene-gui/model/gui_window_world_map.h"
namespace Narradia
{
   void KbBindingsModule::UpdateGameLogic() {
      if (KbInput::get()->KeyHasBeenFiredPickResult(SDLK_m)) {
         GuiWindowWorldMap::get()->ToggleVisibility();
      }
   }
}
