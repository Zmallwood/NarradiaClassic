#pragma once
namespace Narradia {
  /**
   Player actor which can move around on the map and engage
   in combat.
  */
  class Player : public Singleton<Player> {
   public:
    Player();
    void MoveForward();
    void MoveRight();
    void MoveBackwards();
    void MoveLeft();
    void MoveAtAngle(float angle_deg_);
    void AddExperience(int amount);
    bool IsMoving();

    auto position() {
      return position_;
    }

    void set_position(Point3F value) {
      position_ = value;
    }

    auto movement_speed() {
      return movement_speed_;
    }

    auto ticks_last_move() {
      return ticks_last_move_;
    }

    void set_ticks_last_move(int value) {
      ticks_last_move_ = value;
    }

    auto destination() {
      return destination_;
    }

    void set_destination(Point value) {
      destination_ = value;
    }

    auto attack_speed() {
      return attack_speed_;
    }

    auto ticks_last_hit_performed() {
      return ticks_last_hit_performed_;
    }

    void set_ticks_last_hit_performed(int value) {
      ticks_last_hit_performed_ = value;
    }

    auto ultimate_skill_chance() {
      return ultimate_skill_chance_;
    }

    auto ticks_ulti_skill_start() {
      return ticks_ulti_skill_start_;
    }

    void set_ticks_ulti_skill_start(int value) {
      ticks_ulti_skill_start_ = value;
    }

    auto ulti_skill_duration() {
      return ulti_skill_duration_;
    }

    auto facing_angle_deg() {
      return facing_angle_deg_;
    }

    void set_facing_angle_deg(float value) {
      facing_angle_deg_ = value;
    }

    auto experience() {
      return experience_;
    }

   private:
    Point3F position_;
    float movement_speed_ = 5.0f;
    int ticks_last_move_ = 0;
    Point destination_ = {-1, -1};
    float attack_speed_ = 0.8f;
    int ticks_last_hit_performed_ = 0;
    float ultimate_skill_chance_ = 0.4f;
    int ticks_ulti_skill_start_ = 0;
    int ulti_skill_duration_ = 9000;
    float facing_angle_deg_ = 0.0f;
    float step_size_ = 0.9f;
    int experience_ = 0;
  };
}
