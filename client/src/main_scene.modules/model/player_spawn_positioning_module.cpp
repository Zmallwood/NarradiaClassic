#include "player_spawn_positioning_module.h"
#include "conf/model/conf.h"
#include "world.actors/model/player.h"
#include "world.structure/model/world.h"
namespace Narradia
{
    void PlayerSpawnPositioningModule::SpawnAtGoodLocation() {
        auto map_area = World::get()->curr_map_area();
        std::shared_ptr<Tile> tile;
        int x;
        int y;
        auto x_center = map_area->GetWidth() / 2;
        auto y_center = map_area->GetHeight() / 2;
        auto r_min = std::min(map_area->GetWidth(), map_area->GetHeight()) / 2;
        do {
            auto angle_deg = static_cast<float>(rand() % 360);
            x = x_center + static_cast<int>((r_min - kShoreSize - 1) * CosDeg(angle_deg));
            y = y_center + static_cast<int>((r_min - kShoreSize - 1) * SinDeg(angle_deg));
            tile = map_area->GetTile(x, y);
        } while (tile->ground() == "GroundWater" || tile->object() || tile->mob());
        Player::get()->set_position({static_cast<float>(x), 0.0f, static_cast<float>(y)});
    }
}