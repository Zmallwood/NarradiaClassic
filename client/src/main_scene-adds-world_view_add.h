#pragma once

namespace Narradia
{
   class WorldViewAdd : public S<WorldViewAdd>
   {
     public:
      WorldViewAdd();
      void UpdateGameLogic();
   };

   // Show Camera class 
#if 1
   class Camera : public S<Camera>
   {
     public:
      void UpdateGameLogic();
      auto horizontal_angle_deg()
      {
         return horizontal_angle_deg_;
      }
      void set_horizontal_angle_deg(float value)
      {
         horizontal_angle_deg_ = value;
      }
      auto vertical_angle_deg()
      {
         return vertical_angle_deg_;
      }
      void set_vertical_angle_deg(float value)
      {
         vertical_angle_deg_ = value;
      }
      auto camera_distance()
      {
         return camera_distance_;
      }
      void set_camera_distance(float value)
      {
         camera_distance_ = value;
      }

     private:
      Point3F GetCameraPosition();

      float camera_height_ = 3.0f;
      float used_fov_ = 90.0f;
      float camera_distance_ = 20.0f;
      float horizontal_angle_deg_ = 0.0f;
      float vertical_angle_deg_ = 160.0f;
   };
#endif
}
