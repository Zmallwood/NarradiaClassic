#pragma once

#include "GuiComponent.h"

namespace Narradia {
   class GuiContainer : public GuiComponent {
     public:
      GuiContainer(PointF _pos, SizeF _size)
          : m_pos(_pos),
            m_size(_size),
            m_guiComponents(MakeShared<Vec<SharedPtr<GuiComponent>>>()) {
      }
      void AddGuiComponent(SharedPtr<GuiComponent> _comp);
      RectF Bounds();

      auto GetPos() {
         return m_pos;
      }
      auto GetSize() {
         return m_size;
      }
      auto GetGuiComponents() {
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
      SharedPtr<Vec<SharedPtr<GuiComponent>>> m_guiComponents;
   };
}
