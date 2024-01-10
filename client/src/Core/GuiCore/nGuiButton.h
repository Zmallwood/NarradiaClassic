#pragma once

#include "nGuiComponent.h"

namespace Narradia {
   class nGuiButton : public nGuiComponent {
     public:
      // clang-format off
      nGuiButton(
         const StringView &_text, 
         RectF _bounds,
         Function<void()> _action,
         StringView _imgName = "GuiButtonBack",
         StringView _hoveredImgName = "GuiButtonBackHovered");
      // clang-format on
      void UpdateGameLogic() override;

      auto Text() {
         return m_text;
      }
      auto Bounds() {
         return m_bounds;
      }
      auto ImgName() {
         return m_imgName;
      }
      auto HoveredImgName() {
         return m_hoveredImgName;
      }
      auto Hovered() {
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
