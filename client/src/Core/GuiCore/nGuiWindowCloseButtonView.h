#pragma once

namespace Narradia {
   class nGuiWindowCloseButton;

   class nGuiWindowCloseButtonView {
     public:
      nGuiWindowCloseButtonView();
      void Render();

      void SetModel(SharedPtr<nGuiWindowCloseButton> _value) {
         m_model = _value;
      }

     private:
      SharedPtr<nGuiWindowCloseButton> m_model;
      RenderID m_RIDCloseButtonImg;
   };
}
