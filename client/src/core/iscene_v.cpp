#if 1
#include "iscene_v.h"
#include "gui-core/scene_gui_v.h"
#endif

namespace Narradia
{
   ISceneV::ISceneV()
       : scene_gui_view_(std::make_shared<SceneGuiV>())
   {
   }
   void ISceneV::Render()
   {
      RenderDerived();
      scene_gui_view_->Render();
   }
}
