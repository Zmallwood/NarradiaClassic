#include "WorldDisplayModuleView.h"
#include "configuration/model/Configuration.h"
#include "core.drawing/view/ImageDrawingView.h"
#include "core/model/Graphics.h"
#include "main_scene.modules/model/TileHoveringModule.h"
#include "main_scene.modules/model/TileInfo.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"
#include "functions/DoDrawGround.h"

namespace Narradia {
    void WorldDisplayModuleView::Render() {
        auto aspect_ratio = GetAspectRatio();
        auto tile_width = kTileWidth;
        auto tile_height = tile_width * aspect_ratio;
        auto map_area = World::Get()->curr_map_area();
        auto player_pos = Player::Get()->position();
        auto hovered_tile = TileHoveringModule::Get()->hovered_tile();

        for (auto y = 0; y < 11; y++) {
            for (auto x = 0; x < 11; x++) {
                auto map_x = player_pos.x - 5 + x;
                auto map_y = player_pos.y - 5 + y;
                auto tile = map_area->GetTile(map_x, map_y);

                TileInfo tile_info;
                
                tile_info.tile = tile;
                tile_info.map_x = map_x;
                tile_info.map_y = map_y;
                tile_info.col = x;
                tile_info.row = y;
                tile_info.tile_width = tile_width;
                tile_info.tile_height = tile_height;

                DoDrawGround(tile_info);

                if (map_x == hovered_tile.x && map_y == hovered_tile.y) {
                    ImageDrawingView::Get()->DrawImage(
                        "HoveredTile", {x * tile_width, y * tile_height,
                                        tile_width, tile_height});
                }

                if (tile->object()) {
                    if (tile->object()->type() != "") {
                        ImageDrawingView::Get()->DrawImage(
                            map_area->GetTile(map_x, map_y)->object()->type(),
                            {x * tile_width, y * tile_height, tile_width,
                             tile_height});
                    }
                }

                if (x == 5 && y == 5)
                    ImageDrawingView::Get()->DrawImage(
                        "Player", {x * tile_width, y * tile_height, tile_width,
                                   tile_height});
            }
        }
    }
}