#pragma once

#include "GuiComponent.h"

namespace Narradia {
   class GuiButton : public GuiComponent {
     public:
      // clang-format off
      GuiButton(
         const StringView &_text, 
         RectF _bounds,
         Function<void()> _action,
         StringView _imgName = "GuiButtonBack",
         StringView _hoveredImgName = "GuiButtonBackHovered");
      // clang-format on
      void UpdateGameLogic() override;

      auto GetText() {
         return m_text;
      }
      auto GetBounds() {
         return m_bounds;
      }
      auto GetImgName() {
         return m_imgName;
      }
      auto GetHoveredImgName() {
         return m_hoveredImgName;
      }
      auto GetHovered() {
         return m_hovered;
      }

     private:
      StringView m_text;
      RectF m_bounds;
      Function<void()> m_action;
      StringView m_imgName;
      StringView m_hoveredImgName;
      bool m_hovered;
   };
}
