#include "engine_view.h"
#include "cursor_view.h"
#include "graphics_view.h"
#include "scene_mngr_view.h"
#include "text_out_box_view.h"
namespace Narradia
{
    /**
     Render game each frame.
    */
    void EngineView::Render() {
        GraphicsView::get()->ClearCanvas();
        SceneMngrView::get()->RenderCurrScene();
        TextOutBoxView::get()->Render();
        CursorView::get()->RenderCursor();
        GraphicsView::get()->PresentCanvas();
    };
}
