#pragma once
namespace Narradia
{
   /**
    Mob actor which can move around and engage in combat.
   */
   class Mob {
     public:
      Mob(std::string type)
          : type_(type) {
      }
      void Hit(float damage);
      bool IsDead();
      void AggroPlayer();

      auto type() {
         return type_;
      }

      auto ticks_last_move() {
         return ticks_last_move_;
      }

      void set_ticks_last_move(int value) {
         ticks_last_move_ = value;
      }

      auto movement_speed() {
         return movement_speed_;
      }

      auto attack_speed() {
         return attack_speed_;
      }

      auto ticks_last_hit_recieved() {
         return ticks_last_hit_recieved_;
      }

      auto ticks_last_hit_performed() {
         return ticks_last_hit_performed_;
      }

      void set_ticks_last_hit_performed(int value) {
         ticks_last_hit_performed_ = value;
      }

      auto health() {
         return health_;
      }

      auto aggroing_player() {
         return aggroing_player_;
      }

     private:
      std::string type_;
      int ticks_last_move_ = 0;
      float movement_speed_ = 1.0f;
      float attack_speed_ = 0.6f;
      float health_ = 10.0f;
      float max_health_ = 10.0f;
      int ticks_last_hit_recieved_ = 0;
      bool aggroing_player_ = false;
      int ticks_last_hit_performed_ = 0;
   };
}
