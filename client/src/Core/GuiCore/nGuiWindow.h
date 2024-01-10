#pragma once

#include "nGuiMovableContainer.h"

namespace Narradia {
   class nGuiWindowCloseButton;

   class nGuiWindow : public nGuiMovableContainer {
     public:
      // clang-format off
      nGuiWindow(
         StringView _title,
         RectF _bounds,
         bool _destroyOnClose = false,
         StringView _bgImageName = "PanelBg");
      // clang-format on
      ~nGuiWindow();
      void Hide();
      void ToggleVisibility();
      RectF AbsTitleBarBounds();

      auto DestroyOnClose() {
         return m_destroyOnClose;
      }
      auto Visible() {
         return m_visible;
      }
      auto BgImageName() {
         return m_bgImageName;
      }
      auto Title() {
         return m_title;
      }
      auto CloseButton() {
         return m_closeButton;
      }

      static constexpr float k_titleBarHeight = 0.03f;
      static constexpr float k_margin = 0.005f;

     protected:
      void UpdateGameLogic() override;

     private:
      virtual void UpdateGameLogicDerived() = 0;

      StringView m_title = "Unnamed window";
      bool m_visible = false;
      bool m_destroyOnClose = false;
      SharedPtr<nGuiWindowCloseButton> m_closeButton;
      StringView m_bgImageName;
   };
}
