#pragma once
#include "core-input/m/mouse_input.h"
#include "core/m/cursor.h"
#include "gui_component.h"
namespace Narradia
{
   class GuiButton : public GuiComponent
   {
     public:
      GuiButton(
          const std::string_view &text, RectF bounds, std::function<void()> action,
          std::string_view img_name = "GuiButtonBack",
          std::string_view hovered_img_name = "GuiButtonBackHovered");

      auto UpdateGameLogic() -> void override;

      auto text()
      {
         return text_;
      }

      auto bounds()
      {
         return bounds_;
      }

      auto img_name()
      {
         return img_name_;
      }

      auto hovered_img_name()
      {
         return hovered_img_name_;
      }

      auto hovered()
      {
         return hovered_;
      }

     private:
      std::string_view text_;
      RectF bounds_;
      std::function<void()> action_;
      std::string_view img_name_;
      std::string_view hovered_img_name_;
      bool hovered_;
   };
}
