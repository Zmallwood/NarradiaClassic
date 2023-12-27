#if 1
#include "iscene_view.h"
#include "gui-core/v/scene_gui_view.h"
#endif

namespace Narradia
{
   ISceneView::ISceneView()
       : scene_gui_view_(std::make_shared<SceneGuiView>())
   {
   }

   auto ISceneView::Render() -> void
   {
      RenderDerived();
      scene_gui_view_->Render();
   }
}
