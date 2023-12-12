#include "iscene_view.h"
namespace Narradia
{
    /**
     Render scenes deriving from this class.
    */
    void ISceneView::Render() {
        RenderDerived();
        scene_gui_view_->Render();
    }
}
