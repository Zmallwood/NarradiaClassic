#pragma once

namespace Narradia {
    class Camera : public Singleton<Camera> {
      public:
        void UpdateGameLogic();

      private:
        Point3F GetCameraPosition();

        float camera_height_ = 3.0f;
        float used_fov_ = 90.0f;
        float camera_distance_ = 3.0f;
        float vertical_angle_ = 45.0f;
        float horizontal_angle_ = 0.0f;
    };
}
