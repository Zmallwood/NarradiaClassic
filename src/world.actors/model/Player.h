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

      private:
        Point position_;
        float movement_speed_ = 2.0f;
        int ticks_last_move_ = 0;
        Point destination_ = {-1, -1};
    };
}