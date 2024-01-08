#pragma once

#include "GuiComponent.h"
#include "GuiButton.h"
#include "GuiContainer.h"
#include "GuiMovableContainer.h"
#include "GuiWindow.h"
#include "GuiWindowCloseButton.h"
#include "SceneGui.h"
#include "GuiComponentView.h"
#include "GuiButtonView.h"
#include "GuiContainerView.h"
#include "GuiMovableContainerView.h"
#include "GuiWindowView.h"

namespace Narradia {


   // View

#if 1




   class GuiWindowCloseButtonV {
     public:
      GuiWindowCloseButtonV();
      void Render();

      void set_model(SharedPtr<GuiWindowCloseButton> value) {
         model_ = value;
      }

     private:
      SharedPtr<GuiWindowCloseButton> model_;
      RenderID rid_close_btn_img_;
   };

   class SceneGuiV {
     public:
      void Render();
      void AddGuiComponentView(SharedPtr<GuiComponentView> comp_view);

      void set_scene_gui(SharedPtr<SceneGui> value) {
         scene_gui_ = value;
      }

     private:
      SharedPtr<SceneGui> scene_gui_;
      Vec<SharedPtr<GuiComponentView>> gui_component_views_;
   };
#endif

}
