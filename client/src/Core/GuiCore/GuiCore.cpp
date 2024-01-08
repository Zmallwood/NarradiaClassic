#include "GuiCore.h"
#include "Core/Core.h"
#include "Core/Rendering/ImagesRendering.h"
#include "Core/Rendering/TextRendering.h"
#include "Pages.h"
#include "Conf/Constants.h"

namespace Narradia {



   // View

#if 1




   // GuiMovableContainerV
#if 1

#endif

   // GuiWindowV
#if 1
#endif

   // GuiWindowCloseButtonV
#if 1
   GuiWindowCloseButtonV::GuiWindowCloseButtonV() {
      rid_close_btn_img_ = NewImage();
   }

   void GuiWindowCloseButtonV::Render() {
      if (model_->GetHovered())
         DrawImage("GuiWindowCloseButtonHovered", rid_close_btn_img_, model_->Bounds());
      else
         DrawImage("GuiWindowCloseButton", rid_close_btn_img_, model_->Bounds());
   }
#endif

   // SceneGuiV
#if 1
   void SceneGuiV::Render() {
      for (auto gui_component_view : gui_component_views_)
         gui_component_view->Render();
   }

   void SceneGuiV::AddGuiComponentView(SharedPtr<GuiComponentView> comp_view) {
      auto comp_model = scene_gui_->GetGuiComponents()->at(gui_component_views_.size());

      comp_view->SetGuiComponent(comp_model);
      gui_component_views_.push_back(comp_view);
   }
#endif
#endif

}
