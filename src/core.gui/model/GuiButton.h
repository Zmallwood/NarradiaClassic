#pragma once
#include "GuiComponent.h"

namespace Narradia {
    /**
     Model component of GuiButton, which is a visible and hoverable button
     which executes an action when clicked.
    */
    class GuiButton : public GuiComponent {
      public:
        GuiButton(
            const std::string_view &text, RectF bounds, std::function<void()> action,
            std::string_view image_name = "GuiButtonBack",
            std::string_view hovered_image_name = "GuiButtonBackHovered");
        void UpdateGameLogic() override;

        std::string_view text() {
            return text_;
        }

        RectF bounds() {
            return bounds_;
        }

        std::string_view image_name() {
            return image_name_;
        }

        std::string_view hovered_image_name() {
            return hovered_image_name_;
        }

        bool hovered() {
            return hovered_;
        }

      private:
        std::string_view text_;
        RectF bounds_;
        std::function<void()> action_;
        std::string_view image_name_;
        std::string_view hovered_image_name_;
        bool hovered_;
    };
}
