#include "mouse_rotation_module.h"
#include "input/m/mouse_input.h"
#include "core/m/cursor.h"
#include "main_scene-modules-world_view/m/camera.h"
#include "world-actors/m/player.h"

namespace Narradia
{
   void MouseRotationModule::UpdateGameLogic()
   {
      MouseInput::get()->right_btn()->AddFiredAction(
          [&]
          {
             is_rotating_ = true;
             mouse_pos_rotation_start_ = MousePosition();
             cam_horizontal_angle_deg_rotation_start_ = Camera::get()->horizontal_angle_deg();
             cam_vertical_angle_deg_rotation_start_ = Camera::get()->vertical_angle_deg();
          },
          1);
      MouseInput::get()->right_btn()->AddReleasedAction([&] { is_rotating_ = false; });
      if (is_rotating_)
      {
         Cursor::get()->set_style(CursorStyles::Rotating);
         auto mouse_pos = MousePosition();
         auto dx = mouse_pos.x - mouse_pos_rotation_start_.x;
         auto dy = mouse_pos.y - mouse_pos_rotation_start_.y;
         Camera::get()->set_horizontal_angle_deg(
             cam_horizontal_angle_deg_rotation_start_ - dx * kRotationSens);
         Camera::get()->set_vertical_angle_deg(
             cam_vertical_angle_deg_rotation_start_ - dy * kRotationSens);
         Player::get()->set_facing_angle_deg(Camera::get()->horizontal_angle_deg());
      }
   }
}
