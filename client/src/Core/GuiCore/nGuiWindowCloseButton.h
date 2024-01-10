#pragma once

namespace Narradia {
   class nGuiWindow;

   class nGuiWindowCloseButton {
     public:
      nGuiWindowCloseButton(nGuiWindow *_parentWindow)
          : m_parentWindow(_parentWindow) {
      }
      ~nGuiWindowCloseButton();
      void UpdateGameLogic();
      RectF Bounds() const;

      auto Hovered() {
         return m_hovered;
      }

     private:
      static constexpr float k_width = 0.01f;
      nGuiWindow *m_parentWindow;
      bool m_hovered = false;
   };
}
