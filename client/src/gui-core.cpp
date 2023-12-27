#if 1
#include "gui-core.h"
#include "core.h"
#include "scenes/main/main_scene.h"
#endif

namespace Narradia
{
   // GuiButton
#if 1
   GuiButton::GuiButton(
       const std::string_view &text, RectF bounds, std::function<void()> action,
       std::string_view img_name, std::string_view hovered_img_name)
   {
      text_ = text;
      bounds_ = bounds;
      action_ = action;
      img_name_ = img_name;
      hovered_img_name_ = hovered_img_name;
   }
   void GuiButton::UpdateGameLogic()
   {
      hovered_ = false;
      auto used_bounds = bounds_;
      //        if (p->parent_container_) {
      //            used_bounds.x +=
      //            p->parent_container_->GetPosition().x;
      //            used_bounds.y +=
      //            p->parent_container_->GetPosition().y;
      //        }
      if (used_bounds.Contains(MousePosition()))
      {
         Cursor::get()->set_style(CursorStyles::Hovering);
         hovered_ = true;
         MouseInput::get()->left_btn()->AddFiredAction([&] { action_(); }, 2);
      }
   }
#endif

   // GuiContainer
#if 1
   void GuiContainer::UpdateGameLogic()
   {
      for (auto &comp : *gui_components_)
         comp->UpdateGameLogic();
   }
   void GuiContainer::AddGuiComponent(std::shared_ptr<GuiComponent> comp)
   {
      gui_components_->push_back(comp);
   }
   RectF GuiContainer::Bounds()
   {
      return {position_.x, position_.y, size_.w, size_.h};
   }
#endif

   // GuiMovableContainer
#if 1
   void GuiMovableContainer::UpdateGameLogic()
   {
      auto mouse_pos = MousePosition();
      auto abs_dragable_area = rel_dragable_area_.Translate(position().x, position().y);
      if (abs_dragable_area.Contains(mouse_pos))
      {
         if (!is_moving_ && !movement_trigger_)
         {
            MouseInput::get()->left_btn()->AddFiredAction(
                [&]
                {
                   self_pos_start_moving_ = position();
                   mouse_pos_start_moving_ = MousePosition();
                   is_moving_ = true;
                },
                SDL_GetTicks());
         }
      }
      if (is_moving_)
      {
         auto dx = mouse_pos.x - mouse_pos_start_moving_.x;
         auto dy = mouse_pos.y - mouse_pos_start_moving_.y;
         set_position({self_pos_start_moving_.x + dx, self_pos_start_moving_.y + dy});
         movement_trigger_ = true;
         MouseInput::get()->left_btn()->AddReleasedAction(
             [&]
             {
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
       std::string_view title, RectF bounds, bool destroy_on_close,
       std::string_view background_image_name)
       : GuiMovableContainer(
             {0.0f, 0.0f, bounds.w, kTitleBarHeight}, bounds.GetPosition(), bounds.GetSize()),
         gui_window_close_button_(
             std::make_shared<GuiWindowCloseButton>(std::shared_ptr<GuiWindow>(this)))
   {
      background_image_name_ = background_image_name;
      title_ = title;
      destroy_on_close_ = destroy_on_close;
   }
   void GuiWindow::Hide()
   {
      visible_ = false;
   }
   void GuiWindow::ToggleVisibility()
   {
      visible_ = !visible_;
   }
   void GuiWindow::UpdateGameLogic()
   {
      if (!visible_)
         return;
      gui_window_close_button_->UpdateGameLogic();
      UpdateGameLogicDerived();
      GuiMovableContainer::UpdateGameLogic();
   }
   RectF GuiWindow::AbsTitleBarBounds()
   {
      return {position().x, position().y, size().w, kTitleBarHeight};
   }
#endif

   // GuiWindowCloseButton
#if 1
   void GuiWindowCloseButton::UpdateGameLogic()
   {
      hovered_ = false;
      if (Bounds().Contains(MousePosition()))
      {
         Cursor::get()->set_style(CursorStyles::Hovering);
         hovered_ = true;
         MouseInput::get()->left_btn()->AddFiredAction(
             [&]
             {
                if (parent_window_->destroy_on_close())
                {
                   if (SceneMngr::get()->curr_scene() == SceneNames::Main)
                   {
                      auto scene_gui = MainScene::get()->scene_gui();
                      scene_gui->RemoveGuiComponent(parent_window_);
                   }
                }
                else
                {
                   parent_window_->Hide();
                }
             },
             SDL_GetTicks() + 100);
      }
   }
   RectF GuiWindowCloseButton::Bounds() const
   {
      auto width = kWidth;
      auto height = WidthToHeight(width);
      return RectF{
          parent_window_->Bounds().x + parent_window_->Bounds().w - width - 0.005f,
          parent_window_->Bounds().y + 0.03f / 2 - height / 2, width, height};
   }
#endif

   // SceneGui
#if 1
   void SceneGui::UpdateGameLogic()
   {
      for (auto comp : *gui_components_)
         comp->UpdateGameLogic();
   }
   void SceneGui::AddGuiComponent(std::shared_ptr<GuiComponent> comp)
   {
      gui_components_->push_back(comp);
   }
   void SceneGui::RemoveGuiComponent(std::shared_ptr<GuiComponent> comp)
   {
      auto i = 0;
      for (auto &entry : *gui_components_)
      {
         if (entry.get() == comp.get())
         {
            gui_components_->erase(gui_components_->begin() + i);
            break;
         }
         i++;
      }
   }
#endif
}
