#if 1
#include "gui-core_v.h"
#include "rend_2d_images_v.h"
#include "rend_text_v.h"
#endif

namespace Narradia
{
   // GuiButtonV
#if 1
   GuiButtonV::GuiButtonV() {
      rid_image = NewImage();
      rid_label_text_ = NewString();
   }
   void GuiButtonV::Render() {
      auto model = std::static_pointer_cast<GuiButton>(gui_component_);
      std::string_view used_image_name;
      if (model->hovered()) {
         used_image_name = model->hovered_img_name();
      }
      else {
         used_image_name = model->img_name();
      }
      auto used_bounds = model->bounds();
      //        if (p->parent_container_) {
      //            used_bounds.x +=
      //            p->parent_container_->GetPosition().x;
      //            used_bounds.y +=
      //            p->parent_container_->GetPosition().y;
      //        }
      DrawImage(used_image_name, rid_image, used_bounds);
      DrawString(rid_label_text_, model->text(), used_bounds.GetCenter(), Colors::wheat, true);
   }
#endif

   // GuiContainerV
#if 1
   void GuiContainerV::Render() {
      for (auto &comp_view : gui_component_views_)
         comp_view->Render();
   }
   void GuiContainerV::AddGuiComponentView(std::shared_ptr<GuiComponentV> comp_view) {
      auto comp_model = gui_container_->gui_components()->at(gui_component_views_.size());
      comp_view->set_gui_component(comp_model);
      gui_component_views_.push_back(comp_view);
   }
#endif

   // GuiMovableContainerV
#if 1
   void GuiMovableContainerV::Render() {
      GuiContainerV::Render();
   }
#endif

   // GuiWindowV
#if 1
   GuiWindowV::GuiWindowV()
       : gui_window_close_button_view_(std::make_shared<GuiWindowCloseButtonV>()) {
      rid_background_ = NewImage();
      rid_title_bar_ = NewImage();
      rid_title_text_ = NewString();
   }
   void GuiWindowV::Render() {
      auto model = static_pointer_cast<GuiWindow>(gui_component_);
      if (!model->visible())
         return;
      DrawImage(model->background_image_name(), rid_background_, model->Bounds());
      DrawImage("GuiWindowTitleBar", rid_title_bar_, model->AbsTitleBarBounds());
      gui_window_close_button_view_->Render();
      DrawString(
          rid_title_text_, model->title(), model->Bounds().GetPosition().Translate(0.005f, 0.01f));
      RenderDerived();
      GuiMovableContainerV::Render();
   }
#endif

   // GuiWindowCloseButtonV
#if 1
   GuiWindowCloseButtonV::GuiWindowCloseButtonV() {
      rid_close_btn_img_ = NewImage();
   }
   void GuiWindowCloseButtonV::Render() {
      if (model_->hovered())
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
   void SceneGuiV::AddGuiComponentView(std::shared_ptr<GuiComponentV> comp_view) {
      auto comp_model = scene_gui_->gui_components()->at(gui_component_views_.size());
      comp_view->set_gui_component(comp_model);
      gui_component_views_.push_back(comp_view);
   }
#endif
}
