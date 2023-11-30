#include "TileHoveringModule.h"
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
        auto map_x = player_pos.x - 5 + col;
        auto map_y = player_pos.y - 5 + row;
        
        hovered_tile_ = {map_x, map_y};
    }
}