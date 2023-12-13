#pragma once
#include "../../common/system/command/utilities.h"
#include "../../core.input/model/mouse_input.h"
#include "../../core/model/cursor.h"
#include "gui_component.h"
#include <functional>
#include <string_view>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Model component of GuiButton, which is a visible and hoverable button which executes
   /// an action when clicked.
   ////////////////////////////////////////////////////////////////////////////////
   class GuiButton : public GuiComponent {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Initializes new GuiButton model.
      ///
      /// @param[in] text Text printed in the middle of button.
      /// @param[in] bounds Outer bounds defining the button geometry.
      /// @param[in] action Action to execute when clicked.
      /// @param[in] image_name Name of image used when not hovered.
      /// @param[in] hovered_image_name Name of image used when hovered.
      ////////////////////////////////////////////////////////////////////////////////
      GuiButton(
          const std::string_view &text, RectF bounds, std::function<void()> action,
          std::string_view img_name = "GuiButtonBack",
          std::string_view hovered_img_name = "GuiButtonBackHovered");

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Sets cursor to hovering style if button is hovered, and executes the button action
      /// if clicked.
      ////////////////////////////////////////////////////////////////////////////////
      auto UpdateGameLogic() -> void override;

      auto text() {
         return text_;
      }

      auto bounds() {
         return bounds_;
      }

      auto img_name() {
         return img_name_;
      }

      auto hovered_img_name() {
         return hovered_img_name_;
      }

      auto hovered() {
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
