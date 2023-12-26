#include "engine_view.h"
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
