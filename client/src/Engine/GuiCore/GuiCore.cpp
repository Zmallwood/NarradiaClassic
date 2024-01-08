#include "GuiCore.h"
#include "Configuration/Configuration.h"
#include "Engine/Core.h"
#include "Engine/Rendering/ImagesRendering.h"
#include "Engine/Rendering/TextRendering.h"
#include "Pages.h"

namespace Narradia {

   // Model

#if 1
   // GuiButton
#if 1
   GuiButton::GuiButton(
       const StringView &text, RectF bounds, Function<void()> action, StringView img_name,
       StringView hovered_img_name) {
      text_ = text;
      bounds_ = bounds;
      action_ = action;
      img_name_ = img_name;
      hovered_img_name_ = hovered_img_name;
   }

   void GuiButton::UpdateGameLogic() {
      hovered_ = false;
      auto used_bounds = bounds_;

      //        if (p->parent_container_) {
      //            used_bounds.x +=
      //            p->parent_container_->GetPosition().x;
      //            used_bounds.y +=
      //            p->parent_container_->GetPosition().y;
      //        }

      if (used_bounds.Contains(MousePosition())) {
         Cursor::get()->set_style(CursorStyles::Hovering);
         hovered_ = true;
         MouseInput::get()->left_btn()->AddFiredAction([&] { action_(); }, 2);
      }
   }
#endif

   // GuiContainer
#if 1
   void GuiContainer::UpdateGameLogic() {
      for (auto &comp : *gui_components_)
         comp->UpdateGameLogic();
   }

   void GuiContainer::AddGuiComponent(SharedPtr<GuiComponent> comp) {
      gui_components_->push_back(comp);
   }

   RectF GuiContainer::Bounds() {
      return {position_.x, position_.y, size_.w, size_.h};
   }
#endif

   // GuiMovableContainer
#if 1
   void GuiMovableContainer::UpdateGameLogic() {
      auto mouse_pos = MousePosition();
      auto abs_dragable_area = rel_dragable_area_.Translate(position().x, position().y);

      if (abs_dragable_area.Contains(mouse_pos)) {
         if (!is_moving_ && !movement_trigger_) {
            MouseInput::get()->left_btn()->AddFiredAction(
                [&] {
                   self_pos_start_moving_ = position();
                   mouse_pos_start_moving_ = MousePosition();
                   is_moving_ = true;
                },
                SDL_GetTicks());
         }
      }

      if (is_moving_) {
         auto dx = mouse_pos.x - mouse_pos_start_moving_.x;
         auto dy = mouse_pos.y - mouse_pos_start_moving_.y;

         set_position({self_pos_start_moving_.x + dx, self_pos_start_moving_.y + dy});
         movement_trigger_ = true;

         MouseInput::get()->left_btn()->AddReleasedAction(
             [&] {
                is_moving_ = false;
                movement_trigger_ = false;
             },
             SDL_GetTicks());
      }

      GuiContainer::UpdateGameLogic();
   }
#endif

   // GuiWindow
#if 1
   GuiWindow::GuiWindow(
       StringView title, RectF bounds, bool destroy_on_close, StringView background_image_name)
       : GuiMovableContainer(
             {0.0f, 0.0f, bounds.w, kTitleBarHeight}, bounds.GetPosition(), bounds.GetSize()),
         gui_window_close_button_(std::make_shared<GuiWindowCloseButton>(this)) {
      background_image_name_ = background_image_name;
      title_ = title;
      destroy_on_close_ = destroy_on_close;
   }

   GuiWindow::~GuiWindow() {
      if (k_verbose)
         std::cout << "Cleaning up GuiWindow.\n";

      gui_window_close_button_ = nullptr;

      if (k_verbose)
         std::cout << "Cleaning up of GuiWindow finished.\n";
   }

   void GuiWindow::Hide() {
      visible_ = false;
   }

   void GuiWindow::ToggleVisibility() {
      visible_ = !visible_;
   }

   void GuiWindow::UpdateGameLogic() {
      if (!visible_)
         return;

      gui_window_close_button_->UpdateGameLogic();
      UpdateGameLogicDerived();
      GuiMovableContainer::UpdateGameLogic();
   }

   RectF GuiWindow::AbsTitleBarBounds() {
      return {position().x, position().y, size().w, kTitleBarHeight};
   }
#endif

   // GuiWindowCloseButton
#if 1
   GuiWindowCloseButton::~GuiWindowCloseButton() {
      if (k_verbose)
         std::cout << "Disposing GuiWindowCloseButton.\n";
   }

   void GuiWindowCloseButton::UpdateGameLogic() {
      hovered_ = false;

      if (Bounds().Contains(MousePosition())) {
         Cursor::get()->set_style(CursorStyles::Hovering);
         hovered_ = true;

         MouseInput::get()->left_btn()->AddFiredAction(
             [&] {
                if (parent_window_->destroy_on_close()) {
                   if (PageMngr::get()->curr_scene() == PageNames::Main) {
                      auto scene_gui = MainPg::get()->scene_gui();
                      scene_gui->RemoveGuiComponent(parent_window_);
                   }
                } else {
                   parent_window_->Hide();
                }
             },
             SDL_GetTicks() + 100);
      }
   }

   RectF GuiWindowCloseButton::Bounds() const {
      auto width = kWidth;
      auto height = WidthToHeight(width);

      return RectF{
          parent_window_->Bounds().x + parent_window_->Bounds().w - width - 0.005f,
          parent_window_->Bounds().y + 0.03f / 2 - height / 2, width, height};
   }
#endif

   // SceneGui
#if 1
   void SceneGui::UpdateGameLogic() {
      for (auto comp : *gui_components_)
         comp->UpdateGameLogic();
   }

   void SceneGui::AddGuiComponent(SharedPtr<GuiComponent> comp) {
      gui_components_->push_back(comp);
   }

   void SceneGui::RemoveGuiComponent(GuiComponent *comp) {
      auto i = 0;

      for (auto &entry : *gui_components_) {
         if (entry.get() == comp) {
            gui_components_->erase(gui_components_->begin() + i);
            break;
         }

         i++;
      }
   }
#endif
#endif

   // View

#if 1
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
      } else {
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

   void GuiContainerV::AddGuiComponentView(SharedPtr<GuiComponentV> comp_view) {
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
       : gui_window_close_button_view_(MakeShared<GuiWindowCloseButtonV>()) {
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

   void SceneGuiV::AddGuiComponentView(SharedPtr<GuiComponentV> comp_view) {
      auto comp_model = scene_gui_->gui_components()->at(gui_component_views_.size());

      comp_view->set_gui_component(comp_model);
      gui_component_views_.push_back(comp_view);
   }
#endif
#endif

}
