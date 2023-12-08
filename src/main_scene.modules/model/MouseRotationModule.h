#pragma once

namespace Narradia {

    class MouseRotationModule : public Singleton<MouseRotationModule> {
      public:
        void UpdateGameLogic();

      private:
        bool is_rotating_ = false;
        PointF mouse_pos_rotation_start_;
        float cam_horizontal_angle_deg_rotation_start_;
        float cam_vertical_angle_deg_rotation_start_;

        const float kRotationSens = 200.0f;
    };
}
