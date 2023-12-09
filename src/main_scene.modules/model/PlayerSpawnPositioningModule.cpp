#include "PlayerSpawnPositioningModule.h"
#include "conf/model/Configuration.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"

namespace Narradia {
    void PlayerSpawnPositioningModule::SpawnAtGoodLocation() {
        auto map_area = World::Get()->curr_map_area();
        auto tile = map_area->GetTile(
            static_cast<int>(Player::Get()->position().x),
            static_cast<int>(Player::Get()->position().y));

        while (tile->ground() == "GroundWater" || tile->object() || tile->mob()) {
            auto new_x = rand() % kMapWidth;
            auto new_y = rand() % kMapHeight;
            tile = map_area->GetTile(new_x, new_y);
            Player::Get()->set_position(
                {static_cast<float>(new_x), 0.0f, static_cast<float>(new_y)});
        }
    }
}
