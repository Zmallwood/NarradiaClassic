#pragma once

namespace Narradia {

   // Model

#if 1
   class FPSCounterAdd : public Singleton<FPSCounterAdd> {
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

   class KeyboardMovementAdd : public Singleton<KeyboardMovementAdd> {
     public:
      void UpdateGameLogic();
   };

   class MouseMovementAdd : public Singleton<MouseMovementAdd> {
     public:
      void UpdateGameLogic();
   };

   class MouseRotationAdd : public Singleton<MouseRotationAdd> {
     public:
      void UpdateGameLogic();

     private:
      bool is_rotating_ = false;
      PointF mouse_pos_rotation_start_;
      float cam_horizontal_angle_deg_rotation_start_;
      float cam_vertical_angle_deg_rotation_start_;

      const float kRotationSens = 200.0f;
   };

   class SkillPerformingAdd : public Singleton<SkillPerformingAdd> {
     public:
      void UpdateGameLogic();

     private:
      int ticks_last_skill_tick_ = 0;
      float skill_ticks_frequency_ = 0.4f;
   };

   class TileHoveringAdd : public Singleton<TileHoveringAdd> {
     public:
      void UpdateGameLogic();
      auto hovered_tile() {
         return hovered_tile_;
      }

     private:
      Point hovered_tile_ = {-1, -1};
   };

   class MenuModelsAdd : public Singleton<MenuModelsAdd> {
     public:
      void UpdateGameLogic();

     private:
      float used_fov_ = 90.0f;
   };

   class KbBindingsAdd : public Singleton<KbBindingsAdd> {
     public:
      void UpdateGameLogic();
   };

   class PlayerSpawnPositioningAdd : public Singleton<PlayerSpawnPositioningAdd> {
     public:
      void SpawnAtGoodLocation();
   };
#endif

   // View

#if 1
   class FPSCounterAddView : public Singleton<FPSCounterAddView> {
     public:
      FPSCounterAddView();
      void Render();

     private:
      RenderID rid_text;
   };

   class MenuModelsAddView : public Singleton<MenuModelsAddView> {
     public:
      void Render();
   };
#endif

}
