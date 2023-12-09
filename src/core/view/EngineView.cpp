#include "EngineView.h"
#include "CursorView.h"
#include "GraphicsView.h"
#include "SceneMngrView.h"
#include "TextOutBoxView.h"

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
