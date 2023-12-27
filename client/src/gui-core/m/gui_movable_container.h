#pragma once

#include "gui_container.h"

namespace Narradia
{
   class GuiMovableContainer : public GuiContainer
   {
     public:
      GuiMovableContainer(RectF rel_dragable_area, PointF position, SizeF size)
          : GuiContainer(position, size),
            rel_dragable_area_(rel_dragable_area)
      {
      }

     protected:
      void UpdateGameLogic() override;

     private:
      RectF rel_dragable_area_;
      bool movement_trigger_ = false;
      bool is_moving_ = false;
      PointF mouse_pos_start_moving_;
      PointF self_pos_start_moving_;
   };
}
