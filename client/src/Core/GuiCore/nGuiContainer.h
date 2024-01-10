#pragma once

#include "nGuiComponent.h"

namespace Narradia {
   class nGuiContainer : public nGuiComponent {
     public:
      nGuiContainer(PointF _pos, SizeF _size)
          : m_pos(_pos),
            m_size(_size),
            m_guiComponents(MakeShared<Vec<SharedPtr<nGuiComponent>>>()) {
      }
      void AddGuiComponent(SharedPtr<nGuiComponent> _comp);
      RectF Bounds();

      auto Pos() {
         return m_pos;
      }
      auto Size() {
         return m_size;
      }
      auto GuiComponents() {
         return m_guiComponents;
      }

     protected:
      void UpdateGameLogic() override;

      void SetPos(PointF _value) {
         m_pos = _value;
      }

     private:
      PointF m_pos;
      SizeF m_size;
      SharedPtr<Vec<SharedPtr<nGuiComponent>>> m_guiComponents;
   };
}
