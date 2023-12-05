#include "GuiButton.h"

namespace Narradia {

    GuiButton::GuiButton(
        const std::string_view &text, RectF bounds,
        std::function<void()> action, const std::string_view &image_name,
        const std::string_view &hovered_image_name) {
        text_ = text;
        bounds_ = bounds;
        action_ = action;
        image_name_ = image_name;
        hovered_image_name_ = hovered_image_name_;
    }

    void GuiButton::UpdateGameLogic() {
    }
}
