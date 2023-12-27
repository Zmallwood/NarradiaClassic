#if 1
#include "engine_view.h"
#include "console_view.h"
#include "cursor_view.h"
#include "graphics_view.h"
#include "scene_mngr_view.h"
#endif

namespace Narradia
{
   auto EngineView::Render() -> void
   {
      GraphicsView::get()->ClearCanvas();
      SceneMngrView::get()->RenderCurrScene();
      ConsoleView::get()->Render();
      CursorView::get()->RenderCursor();
      GraphicsView::get()->PresentCanvas();
   };
}
