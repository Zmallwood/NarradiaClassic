#pragma once

namespace Narradia {
   class GuiWindow;

   class GuiWindowCloseButton {
     public:
      GuiWindowCloseButton(GuiWindow *_parentWindow)
          : m_parentWindow(_parentWindow) {
      }
      ~GuiWindowCloseButton();
      void UpdateGameLogic();
      RectF Bounds() const;

      auto GetHovered() {
         return m_hovered;
      }

     private:
      static constexpr float k_width = 0.01f;
      GuiWindow *m_parentWindow;
      bool m_hovered = false;
   };
}
