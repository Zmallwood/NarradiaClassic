#pragma once
#include "GuiComponent.h"

namespace Narradia {
    class GuiButton : public GuiComponent {
      public:
        GuiButton(
            const std::string_view &text, RectF bounds,
            std::function<void()> action,
            const std::string_view &image_name = "GuiButtonBack",
            const std::string_view &hovered_image_name =
                "GuiButtonBackHovered");

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
