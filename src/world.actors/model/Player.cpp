#include "Player.h"
#include "configuration/model/Configuration.h"

namespace Narradia {
    /**
     * Set default spawn coordinate.
     */
    Player::Player() {
        position_ = {kMapWidth / 2, kMapHeight / 2};
        position_3d_ = {kMapWidth / 2.0f, 0.0f, kMapHeight / 2.0f};
    }

    void Player::MoveUp() {
        position_.y--;
    }

    void Player::MoveRight() {
        position_.x++;
    }

    void Player::MoveDown() {
        position_.y++;
    }

    void Player::MoveLeft() {
        position_.x--;
    }
}
