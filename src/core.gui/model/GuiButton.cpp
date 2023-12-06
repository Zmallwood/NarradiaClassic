#include "GuiButton.h"
#include "common/system/functions/Utilities.h"
#include "core.input/model/MouseInput.h"

namespace Narradia {

    GuiButton::GuiButton(
        const std::string_view &text, RectF bounds,
        std::function<void()> action, std::string_view image_name,
        std::string_view hovered_image_name) {
        text_ = text;
        bounds_ = bounds;
        action_ = action;
        image_name_ = image_name;
        hovered_image_name_ = hovered_image_name;
    }

    void GuiButton::UpdateGameLogic() {
        hovered_ = false;
        auto used_bounds = bounds_;
        //        if (p->parent_container_) {
        //            used_bounds.x += p->parent_container_->GetPosition().x;
        //            used_bounds.y += p->parent_container_->GetPosition().y;
        //        }
        if (used_bounds.Contains(GetMousePosition())) {
            //            Cursor::Get()->SetCursorType(CursorTypes::Hovering);
            hovered_ = true;
            MouseInput::Get()
                ->left_button()
                ->mouse_action_mngr()
                ->AddFiredAction([&] { action_(); }, 1);
            //            MouseInput::Get()->GetLeftButton().AddFiredAction(
            //                "PerformGuiButtonAction", [&] { p->action_(); },
            //                1);
            // std::cout << "inside\n";
        }
        else {
            // std::cout << "outside, x:"  << GetMousePosition().x << " y:" <<
            // GetMousePosition().y << std::endl;
        }
    }
}