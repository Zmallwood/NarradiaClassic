#include "WorldDisplayModuleView.h"
#include "common/system/functions/Utilities.h"
#include "configuration/model/Configuration.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "core.render/view/Renderer2DSolidColorsView.h"
#include "functions/DoDrawGround.h"
#include "functions/DoDrawObjects.h"
#include "functions/DoDrawPlayer.h"
#include "functions/DoDrawTileSymbols.h"
#include "functions/DoDrawMobs.h"
#include "main_2d_scene.modules/model/TileInfo.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"

namespace Narradia {
    WorldDisplayModuleView::WorldDisplayModuleView() {
        for (auto x = 0; x < GetNumGridCols(); x++) {
            rids_ground.push_back(std::vector<RenderId>());
            rids_objects.push_back(std::vector<RenderId>());
            for (auto y = 0; y < GetNumGridRows(); y++) {
                rids_ground.at(x).push_back(
                    Renderer2DImagesView::Get()->NewImage());
                rids_objects.at(x).push_back(
                    Renderer2DImagesView::Get()->NewImage());
            }
        }
    }

    void WorldDisplayModuleView::Render() {
        auto aspect_ratio = GetAspectRatio();
        auto tile_width = kTileWidth;
        auto tile_height = tile_width * aspect_ratio;
        auto map_area = World::Get()->curr_map_area();
        auto player_pos = Player::Get()->position();

        for (auto y = 0; y < GetNumGridRows(); y++) {
            for (auto x = 0; x < GetNumGridCols(); x++) {
                auto map_x = player_pos.x - GetGridCenterX() + x;
                auto map_y = player_pos.y - GetGridCenterY() + y;

                if (map_x < 0 || map_y < 0 || map_x >= kMapWidth ||
                    map_y >= kMapHeight)
                    continue;

                auto tile = map_area->GetTile(map_x, map_y);

                TileInfo tile_info;

                tile_info.tile = tile;
                tile_info.map_x = map_x;
                tile_info.map_y = map_y;
                tile_info.col = x;
                tile_info.row = y;
                tile_info.tile_width = tile_width;
                tile_info.tile_height = tile_height;
                tile_info.rid_ground = rids_ground[x][y];
                tile_info.rid_object = rids_objects[x][y];

                DoDrawGround(tile_info);
                DoDrawTileSymbols(tile_info);
                DoDrawObjects(tile_info);
                DoDrawMobs(tile_info);
                DoDrawPlayer(tile_info);
            }
        }
    }
}