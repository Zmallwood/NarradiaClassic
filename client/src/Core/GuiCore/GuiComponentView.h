#pragma once

namespace Narradia {
   class GuiComponent;

   class GuiComponentView {
     public:
      virtual void Render() = 0;

      auto GetGuiComponent() {
         return m_guiComponent;
      }
      void SetGuiComponent(SharedPtr<GuiComponent> _value) {
         m_guiComponent = _value;
      }

     protected:
      SharedPtr<GuiComponent> m_guiComponent;
   };
}
