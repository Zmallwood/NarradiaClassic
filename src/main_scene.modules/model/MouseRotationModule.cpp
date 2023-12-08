#include "MouseRotationModule.h"
#include "core.input/model/MouseInput.h"
#include "core/model/Cursor.h"
#include "main_scene.modules.world_view/model/Camera.h"
#include "world.actors/model/Player.h"

namespace Narradia {
    void MouseRotationModule::UpdateGameLogic() {
        MouseInput::Get()->right_button()->AddFiredAction([&] {
            is_rotating_ = true;
            mouse_pos_rotation_start_ = GetMousePosition();
            cam_horizontal_angle_deg_rotation_start_ = Camera::Get()->horizontal_angle_deg();
            cam_vertical_angle_deg_rotation_start_ = Camera::Get()->vertical_angle_deg();
        });
        MouseInput::Get()->right_button()->AddReleasedAction([&] { is_rotating_ = false; });
        if (is_rotating_) {
            Cursor::Get()->set_cursor_style(CursorStyles::Rotating);
            auto mouse_pos = GetMousePosition();
            auto dx = mouse_pos.x - mouse_pos_rotation_start_.x;
            auto dy = mouse_pos.y - mouse_pos_rotation_start_.y;
            Camera::Get()->set_horizontal_angle_deg(
                cam_horizontal_angle_deg_rotation_start_ + dx * kRotationSens);
            Camera::Get()->set_vertical_angle_deg(
                cam_vertical_angle_deg_rotation_start_ + dy * kRotationSens);
            Player::Get()->set_facing_angle_deg(Camera::Get()->horizontal_angle_deg());
        }
    }
}
