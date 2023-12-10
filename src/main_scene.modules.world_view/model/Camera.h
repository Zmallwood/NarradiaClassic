#pragma once

namespace Narradia {
    class Camera : public Singleton<Camera> {
      public:
        void UpdateGameLogic();

        auto horizontal_angle_deg() {
            return horizontal_angle_deg_;
        }

        void set_horizontal_angle_deg(float value) {
            horizontal_angle_deg_ = value;
        }

        auto vertical_angle_deg() {
            return vertical_angle_deg_;
        }

        void set_vertical_angle_deg(float value) {
            vertical_angle_deg_ = value;
        }

      private:
        Point3F GetCameraPosition();

        float camera_height_ = 3.0f;
        float used_fov_ = 90.0f;
        float camera_distance_ = 30.0f;
        float horizontal_angle_deg_ = 0.0f;
        float vertical_angle_deg_ = 130.0f;
    };
}
