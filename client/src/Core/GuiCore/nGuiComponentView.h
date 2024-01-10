#pragma once

namespace Narradia {
   class nGuiComponent;

   class nGuiComponentView {
     public:
      virtual void Render() = 0;

      auto GuiComponent() {
         return m_guiComponent;
      }
      void SetGuiComponent(SharedPtr<nGuiComponent> _value) {
         m_guiComponent = _value;
      }

     protected:
      SharedPtr<nGuiComponent> m_guiComponent;
   };
}
