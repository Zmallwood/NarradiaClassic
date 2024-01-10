#pragma once

#include "nGuiContainer.h"

namespace Narradia {
   class GuiMovableContainer : public GuiContainer {
     public:
      GuiMovableContainer(RectF _relDragableArea, PointF _pos, SizeF _size)
          : GuiContainer(_pos, _size),
            m_relDragableArea(_relDragableArea) {
      }

     protected:
      void UpdateGameLogic() override;

     private:
      RectF m_relDragableArea;
      bool m_movementTrigger = false;
      bool m_isMoving = false;
      PointF m_mousePosStartMoving;
      PointF m_selfPosStartMoving;
   };
}
