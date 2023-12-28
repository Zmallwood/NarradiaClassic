#pragma once

namespace Narradia
{
   class FPSCounterModule : public S<FPSCounterModule>
   {
     public:
      void UpdateGameLogic();
      auto fps()
      {
         return fps_;
      }

     private:
      int fps_ = 0;
      int frames_count_ = 0;
      int ticks_last_update_ = 0;

      static constexpr int kMillisPerSecond = 1000;
   };

   class Mob;

   class MobTargetingModule : public S<MobTargetingModule>
   {
     public:
      void UpdateGameLogic();
      void ClearTarget();
      auto targeted_mob()
      {
         return targeted_mob_;
      }

     private:
      std::shared_ptr<Mob> targeted_mob_;
   };

   class KeyboardMovementModule : public S<KeyboardMovementModule>
   {
     public:
      void UpdateGameLogic();
   };

   class CombatChaseMovementModule : public S<CombatChaseMovementModule>
   {
     public:
      void UpdateGameLogic();
   };

   class MouseMovementModule : public S<MouseMovementModule>
   {
     public:
      void UpdateGameLogic();
   };

   class MobMovementModule : public S<MobMovementModule>
   {
     public:
      void UpdateGameLogic();
   };

   class MouseRotationModule : public S<MouseRotationModule>
   {
     public:
      void UpdateGameLogic();

     private:
      bool is_rotating_ = false;
      PointF mouse_pos_rotation_start_;
      float cam_horizontal_angle_deg_rotation_start_;
      float cam_vertical_angle_deg_rotation_start_;

      const float kRotationSens = 200.0f;
   };

   class SkillPerformingModule : public S<SkillPerformingModule>
   {
     public:
      void UpdateGameLogic();

     private:
      int ticks_last_skill_tick_ = 0;
      float skill_ticks_frequency_ = 0.4f;
   };

   class TileHoveringModule : public S<TileHoveringModule>
   {
     public:
      void UpdateGameLogic();
      auto hovered_tile()
      {
         return hovered_tile_;
      }

     private:
      Point hovered_tile_ = {-1, -1};
   };
}
