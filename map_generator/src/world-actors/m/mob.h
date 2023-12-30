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

        auto type() {
            return type_;
        }

        auto movement_speed() {
            return movement_speed_;
        }

        auto attack_speed() {
            return attack_speed_;
        }

        auto hp() {
            return hp_;
        }
      private:
        std::string type_;
        float movement_speed_ = 1.0f;
        float attack_speed_ = 0.6f;
        float hp_ = 10.0f;
        float max_hp_ = 10.0f;
    };
}
