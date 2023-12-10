#include "draw_tile_symbols.h"
#include "core.render/view/command/draw_tile.h"
#include "main_scene.modules/model/tile_hovering_module.h"

namespace Narradia {
  void DrawTileSymbols(std::shared_ptr<Tile> tile, Point coord) {
    auto hovered_tile = TileHoveringModule::Get()->hovered_tile();
    if (hovered_tile.x == coord.x && hovered_tile.y == coord.y) {
      DrawTile("TileHovered", tile->rid());
    }
  }
}
