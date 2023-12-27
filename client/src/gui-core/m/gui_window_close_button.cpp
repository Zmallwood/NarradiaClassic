#include "gui_window_close_button.h"
#include "input/m/mouse_input.h"
#include "core/m/cursor.h"
#include "core/m/scene_mngr.h"
#include "scenes/main/m/main_scene.h"
#include "gui_window.h"

namespace Narradia
{
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
}
