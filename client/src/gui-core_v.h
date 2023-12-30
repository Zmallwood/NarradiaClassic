#pragma once

#include "gui-core.h"

namespace Narradia
{
   class GuiComponentV {
     public:
      virtual void Render() = 0;
      auto gui_component() {
         return gui_component_;
      }
      void set_gui_component(std::shared_ptr<GuiComponent> value) {
         gui_component_ = value;
      }

     protected:
      std::shared_ptr<GuiComponent> gui_component_;
   };

   class GuiButtonV : public GuiComponentV {
     public:
      GuiButtonV();
      void Render() override;

     private:
      RenderID rid_image;
      RenderID rid_label_text_;
   };

   class GuiContainerV : public GuiComponentV {
     protected:
      void Render() override;
      void AddGuiComponentView(std::shared_ptr<GuiComponentV> comp_view);
      void set_gui_container(std::shared_ptr<GuiContainer> value) {
         gui_container_ = value;
      }

     private:
      std::shared_ptr<GuiContainer> gui_container_;
      std::vector<std::shared_ptr<GuiComponentV>> gui_component_views_;
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
      std::shared_ptr<GuiWindowCloseButtonV> gui_window_close_button_view_;
   };

   class GuiWindowCloseButtonV {
     public:
      GuiWindowCloseButtonV();
      void Render();
      void set_model(std::shared_ptr<GuiWindowCloseButton> value) {
         model_ = value;
      }

     private:
      std::shared_ptr<GuiWindowCloseButton> model_;
      RenderID rid_close_btn_img_;
   };

   class SceneGuiV {
     public:
      void Render();
      void AddGuiComponentView(std::shared_ptr<GuiComponentV> comp_view);
      void set_scene_gui(std::shared_ptr<SceneGui> value) {
         scene_gui_ = value;
      }

     private:
      std::shared_ptr<SceneGui> scene_gui_;
      std::vector<std::shared_ptr<GuiComponentV>> gui_component_views_;
   };
}
