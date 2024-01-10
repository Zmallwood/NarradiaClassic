#pragma once

#include "nGuiContainer.h"

namespace Narradia {
   class nGuiMovableContainer : public nGuiContainer {
     public:
      nGuiMovableContainer(RectF _relDragableArea, PointF _pos, SizeF _size)
          : nGuiContainer(_pos, _size),
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
