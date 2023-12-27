#include "iscene_view.h"

namespace Narradia
{
   auto ISceneView::Render() -> void
   {
      RenderDerived();
      scene_gui_view_->Render();
   }
}
