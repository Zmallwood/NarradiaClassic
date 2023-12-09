#include "Player.h"
#include "configuration/model/Configuration.h"

namespace Narradia
{
    /**
     * Set default spawn coordinate.
     */
    Player::Player() { position_ = {kMapWidth / 2.0f, 0.0f, kMapHeight / 2.0f}; }

    void Player::MoveUp() { position_.z--; }

    void Player::MoveRight() { position_.x++; }

    void Player::MoveDown() { position_.z++; }

    void Player::MoveLeft() { position_.x--; }
}
