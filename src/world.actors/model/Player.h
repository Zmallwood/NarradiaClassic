#pragma once

namespace Narradia {
    class Player : public Singleton<Player> {
      public:
        Player();

        void MoveUp();

        void MoveRight();

        void MoveDown();

        void MoveLeft();

        Point position() {
            return position_;
        }

        void set_position(Point value) {
            position_ = value;
        }

        float movement_speed() {
            return movement_speed_;
        }

        int ticks_last_move() {
            return ticks_last_move_;
        }

        void set_ticks_last_move(int value) {
            ticks_last_move_ = value;
        }

        Point destination() {
            return destination_;
        }

        void set_destination(Point value) {
            destination_ = value;
        }

        float attack_speed() {
            return attack_speed_;
        }

        int ticks_last_hit_performed() {
            return ticks_last_hit_performed_;
        }

        void set_ticks_last_hit_performed(int value) {
            ticks_last_hit_performed_ = value;
        }

        float ultimate_skill_chance() {
            return ultimate_skill_chance_;
        }

        int ticks_ulti_skill_start() {
            return ticks_ulti_skill_start_;
        }

        void set_ticks_ulti_skill_start(int value) {
            ticks_ulti_skill_start_ = value;
        }

        float ulti_skill_duration() {
            return ulti_skill_duration_;
        }

      private:
        Point position_;
        float movement_speed_ = 2.0f;
        int ticks_last_move_ = 0;
        Point destination_ = {-1, -1};
        float attack_speed_ = 0.8f;
        int ticks_last_hit_performed_ = 0;
        float ultimate_skill_chance_ = 0.4f;
        int ticks_ulti_skill_start_ = 0;
        int ulti_skill_duration_ = 9000;
    };
}
