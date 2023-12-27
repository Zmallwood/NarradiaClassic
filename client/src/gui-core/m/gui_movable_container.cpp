#include "gui_movable_container.h"
#include "input/m/mouse_input.h"

namespace Narradia
{
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
}
