#pragma once

#include "GuiComponent.h"
#include "GuiButton.h"
#include "GuiContainer.h"
#include "GuiMovableContainer.h"
#include "GuiWindow.h"
#include "GuiWindowCloseButton.h"
#include "SceneGui.h"
#include "GuiComponentView.h"

namespace Narradia {

   // Model

#if 1

#endif

   // View

#if 1


   class GuiButtonV : public GuiComponentView {
     public:
      GuiButtonV();
      void Render() override;

     private:
      RenderID rid_image;
      RenderID rid_label_text_;
   };

   class GuiContainerV : public GuiComponentView {
     protected:
      void Render() override;
      void AddGuiComponentView(SharedPtr<GuiComponentView> comp_view);

      void set_gui_container(SharedPtr<GuiContainer> value) {
         gui_container_ = value;
      }

     private:
      SharedPtr<GuiContainer> gui_container_;
      Vec<SharedPtr<GuiComponentView>> gui_component_views_;
   };

   class GuiMovableContainerV : public GuiContainerV {
     protected:
      void Render() override;
   };

   class GuiWindowCloseButtonV;

   class GuiWindowV : public GuiMovableContainerV {
     public:
      GuiWindowV();

      auto gui_window_close_button_view() {
         return gui_window_close_button_view_;
      }

     protected:
      virtual void RenderDerived() = 0;

     private:
      void Render() override;

      RenderID rid_background_;
      RenderID rid_title_bar_;
      RenderID rid_title_text_;
      SharedPtr<GuiWindowCloseButtonV> gui_window_close_button_view_;
   };

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
