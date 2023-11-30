#include "Player.h"
#include "configuration/model/Configuration.h"

namespace Narradia {
    Player::Player() {
        position_ = {kMapWidth / 2, kMapHeight / 2};
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