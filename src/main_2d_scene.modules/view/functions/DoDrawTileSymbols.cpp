#include "DoDrawTileSymbols.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "main_2d_scene.modules/model/MobTargetingModule.h"
#include "main_2d_scene.modules/model/TileHoveringModule.h"
#include "world.structure/model/Tile.h"

namespace Narradia {
    void DoDrawTileSymbols(TileInfo tile_info) {
        static RenderId rid_symbol = Renderer2DImagesView::Get()->NewImage();
        auto hovered_tile = TileHoveringModule::Get()->hovered_tile();

        if (tile_info.map_x == hovered_tile.x &&
            tile_info.map_y == hovered_tile.y) {
            Renderer2DImagesView::Get()->DrawImage(
                "HoveredTile", rid_symbol,
                {tile_info.col * tile_info.tile_width,
                 tile_info.row * tile_info.tile_height, tile_info.tile_width,
                 tile_info.tile_height});
        }

        if (tile_info.tile->mob() ==
                MobTargetingModule::Get()->targeted_mob() &&
            nullptr != MobTargetingModule::Get()->targeted_mob()) {
            Renderer2DImagesView::Get()->DrawImage(
                "TileTargetedMob", rid_symbol,
                {tile_info.col * tile_info.tile_width,
                 tile_info.row * tile_info.tile_height, tile_info.tile_width,
                 tile_info.tile_height});
        }
    }
}
