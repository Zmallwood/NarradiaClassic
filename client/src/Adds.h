#pragma once

namespace Narradia
{

// Model

#if 1
   class FPSCounterAdd : public S<FPSCounterAdd> {
     public:
      void UpdateGameLogic();

      auto fps() {
         return fps_;
      }

     private:
      int fps_ = 0;
      int frames_count_ = 0;
      int ticks_last_update_ = 0;

      static constexpr int kMillisPerSecond = 1000;
   };

   class KeyboardMovementAdd : public S<KeyboardMovementAdd> {
     public:
      void UpdateGameLogic();
   };

   class MouseMovementAdd : public S<MouseMovementAdd> {
     public:
      void UpdateGameLogic();
   };

   class MouseRotationAdd : public S<MouseRotationAdd> {
     public:
      void UpdateGameLogic();

     private:
      bool is_rotating_ = false;
      PointF mouse_pos_rotation_start_;
      float cam_horizontal_angle_deg_rotation_start_;
      float cam_vertical_angle_deg_rotation_start_;

      const float kRotationSens = 200.0f;
   };

   class SkillPerformingAdd : public S<SkillPerformingAdd> {
     public:
      void UpdateGameLogic();

     private:
      int ticks_last_skill_tick_ = 0;
      float skill_ticks_frequency_ = 0.4f;
   };

   class TileHoveringAdd : public S<TileHoveringAdd> {
     public:
      void UpdateGameLogic();
      auto hovered_tile() {
         return hovered_tile_;
      }

     private:
      Point hovered_tile_ = {-1, -1};
   };

   class MenuModelsAdd : public S<MenuModelsAdd> {
     public:
      void UpdateGameLogic();

     private:
      float used_fov_ = 90.0f;
   };

   class KbBindingsAdd : public S<KbBindingsAdd> {
   public:
      void UpdateGameLogic();
   };

   class PlayerSpawnPositioningAdd : public S<PlayerSpawnPositioningAdd> {
   public:
      void SpawnAtGoodLocation();
   };
#endif

// View

#if 1
   class FPSCounterAddV : public S<FPSCounterAddV> {
     public:
      FPSCounterAddV();
      void Render();

     private:
      RenderID rid_text;
   };

   class MenuModelsAddV : public S<MenuModelsAddV> {
     public:
      void Render();
   };
#endif

}
