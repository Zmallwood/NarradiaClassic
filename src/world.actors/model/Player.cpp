#include "Player.h"
#include "conf/model/Configuration.h"

namespace Narradia {
    /**
     Set default spawn coordinate.
    */
    Player::Player() {
        position_ = {kMapWidth / 2.0f, 0.0f, kMapHeight / 2.0f};
    }

    void Player::MoveForward() {
        MoveAtAngle(0.0f);
    }

    void Player::MoveRight() {
        MoveAtAngle(90.0f);
    }

    void Player::MoveBackwards() {
        MoveAtAngle(180.0f);
    }

    void Player::MoveLeft() {
        MoveAtAngle(-90.0f);
    }

    void Player::MoveAtAngle(float angle_deg_) {
        auto used_angle = angle_deg_ - facing_angle_deg_;
        auto dx = CosDeg(used_angle + 90.0f) * step_size_;
        auto dz = SinDeg(used_angle + 90.0f) * step_size_;
        position_.x += dx;
        position_.z += dz;
    }
}
