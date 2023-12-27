#if 1
#include "engine_v.h"
#include "console_v.h"
#include "cursor_v.h"
#include "graphics_v.h"
#include "scene_mngr_v.h"
#endif

namespace Narradia
{
   void EngineV::Render()
   {
      GraphicsV::get()->ClearCanvas();
      SceneMngrV::get()->RenderCurrScene();
      ConsoleV::get()->Render();
      CursorV::get()->RenderCursor();
      GraphicsV::get()->PresentCanvas();
   };
}
