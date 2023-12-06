#include "TileHoveringModule.h"
#include "common/system/functions/Utilities.h"
#include "configuration/model/Configuration.h"
#include "world.actors/model/Player.h"

namespace Narradia {
    void TileHoveringModule::UpdateGameLogic() {
        auto mouse_pos = GetMousePosition();
        auto tile_width = kTileWidth;
        auto tile_height = tile_width * GetAspectRatio();
        auto player_pos = Player::Get()->position();
        auto col = mouse_pos.x / tile_width;
        auto row = mouse_pos.y / tile_height;
        auto map_x = static_cast<int>(player_pos.x - GetGridCenterX() + col);
        auto map_y = static_cast<int>(player_pos.y - GetGridCenterY() + row);

        if (map_x < 0 || map_y < 0 || map_x >= kMapWidth || map_y >= kMapHeight)
            return;

        hovered_tile_ = {map_x, map_y};
    }
}
