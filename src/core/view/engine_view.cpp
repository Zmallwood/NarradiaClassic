#include "engine_view.h"
#include "cursor_view.h"
#include "graphics_view.h"
#include "scene_mngr_view.h"
#include "text_out_box_view.h"

namespace Narradia {
  /**
   Render game each frame.
  */
  void EngineView::Render() {
    GraphicsView::Get()->ClearCanvas();
    SceneMngrView::Get()->RenderCurrScene();
    TextOutBoxView::Get()->Render();
    CursorView::Get()->RenderCursor();
    GraphicsView::Get()->PresentCanvas();
  };
}
