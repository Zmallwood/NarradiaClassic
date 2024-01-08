#pragma once

#include "GuiMovableContainer.h"

namespace Narradia {
   class GuiWindowCloseButton;

   class GuiWindow : public GuiMovableContainer {
     public:
      // clang-format off
      GuiWindow(
         StringView _title,
         RectF _bounds,
         bool _destroyOnClose = false,
         StringView _bgImageName = "PanelBg");
      // clang-format on
      ~GuiWindow();
      void Hide();
      void ToggleVisibility();
      RectF AbsTitleBarBounds();

      auto GetDestroyOnClose() {
         return m_destroyOnClose;
      }
      auto GetVisible() {
         return m_visible;
      }
      auto GetBgImageName() {
         return m_bgImageName;
      }
      auto GetTitle() {
         return m_title;
      }
      auto GetCloseButton() {
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
      SharedPtr<GuiWindowCloseButton> m_closeButton;
      StringView m_bgImageName;
   };
}
