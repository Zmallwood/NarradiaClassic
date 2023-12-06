#pragma once

namespace Narradia {
    class Mob {
      public:
        Mob(std::string_view type)
            : type_(type) {
        }

        std::string_view type() {
            return type_;
        }

        int ticks_last_move() {
            return ticks_last_move_;
        }

        void set_ticks_last_move(int value) {
            ticks_last_move_ = value;
        }

        float movement_speed() {
            return movement_speed_;
        }

      private:
        std::string_view type_;
        int ticks_last_move_ = 0;
        float movement_speed_ = 1.0f;
    };
}
