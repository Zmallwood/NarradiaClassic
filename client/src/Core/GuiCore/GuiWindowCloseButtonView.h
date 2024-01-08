#pragma once

namespace Narradia {
   class GuiWindowCloseButton;

   class GuiWindowCloseButtonView {
     public:
      GuiWindowCloseButtonView();
      void Render();

      void SetModel(SharedPtr<GuiWindowCloseButton> _value) {
         m_model = _value;
      }

     private:
      SharedPtr<GuiWindowCloseButton> m_model;
      RenderID m_RIDCloseButtonImg;
   };
}
