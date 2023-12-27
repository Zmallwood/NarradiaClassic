#if 1
#include "iscene.h"
#include "gui-core/scene_gui.h"
#endif

namespace Narradia
{
   IScene::IScene()
       : scene_gui_(std::make_shared<SceneGui>())
   {
   }
   void IScene::UpdateGameLogic()
   {
      UpdateGameLogicDerived();
      scene_gui_->UpdateGameLogic();
   }
}
