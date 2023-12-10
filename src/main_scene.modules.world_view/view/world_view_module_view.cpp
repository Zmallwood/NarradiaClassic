#include "world_view_module_view.h"
#include "command/draw_ground.h"
#include "command/draw_mob.h"
#include "command/draw_objects.h"
#include "command/draw_player.h"
#include "command/draw_tile_symbols.h"
#include "conf/model/conf.h"
#include "core.render/view/command/new_tile.h"
#include "core.render/view/command/set_tile_geometry.h"
#include "core.render/view/command/start_tile_batch_drawing.h"
#include "core.render/view/command/stop_tile_batch_drawing.h"
#include "core.render/view/renderer_tiles_view.h"
#include "world.actors/model/player.h"
#include "world.structure/model/world.h"

namespace Narradia {
  WorldViewModuleView::WorldViewModuleView() {
    auto map_area = World::Get()->curr_map_area();
    auto tile_size = kTileSize;
    for (auto x = 0; x < kMapWidth; x++) {
      rids_tiles.push_back(std::vector<RenderID>());
      rids_tile_symbols.push_back(std::vector<RenderID>());
      for (auto y = 0; y < kMapHeight; y++) {
        rids_tiles.at(x).push_back(NewTile());
        Vertex3F v0;
        Vertex3F v1;
        Vertex3F v2;
        Vertex3F v3;
        v0.position = {x * tile_size, 0.0f * tile_size, y * tile_size};
        v1.position = {x * tile_size + tile_size, 0.0f * tile_size, y * tile_size};
        v2.position = {x * tile_size + tile_size, 0.0f * tile_size, y * tile_size + tile_size};
        v3.position = {x * tile_size, 0.0f * tile_size, y * tile_size + tile_size};
        v0.uv = {0.0f, 0.0f};
        v1.uv = {1.0f, 0.0f};
        v2.uv = {1.0f, 1.0f};
        v3.uv = {0.0f, 1.0f};
        Point3F normal00 = {0.0f, 1.f, 0.0f};
        Point3F normal10 = {0.0f, 1.f, 0.0f};
        Point3F normal11 = {0.0f, 1.f, 0.0f};
        Point3F normal01 = {0.0f, 1.f, 0.0f};
        SetTileGeometry(rids_tiles[x][y], v0, v1, v2, v3, normal00, normal10, normal11, normal01);
        map_area->GetTile(x, y)->set_rid(rids_tiles[x][y]);
        rids_tile_symbols.at(x).push_back(NewTile());
        v0.position.y += kTinyDistance * kTileSize;
        v1.position.y += kTinyDistance * kTileSize;
        v2.position.y += kTinyDistance * kTileSize;
        v3.position.y += kTinyDistance * kTileSize;
        SetTileGeometry(
            rids_tile_symbols[x][y], v0, v1, v2, v3, normal00, normal10, normal11, normal01);
      }
    }
  }

  void WorldViewModuleView::Render() {
    auto map_area = World::Get()->curr_map_area();
    auto player_pos = Player::Get()->position();
    auto r = 20;
    auto x_center = static_cast<int>(player_pos.x);
    auto y_center = static_cast<int>(player_pos.z);
    StartTileBatchDrawing();
    for (auto y = y_center - r; y <= y_center + r; y++) {
      for (auto x = x_center - r; x <= x_center + r; x++) {
        if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
          continue;
        auto dx = x - x_center;
        auto dy = y - y_center;
        if (dx * dx + dy * dy > r * r)
          continue;
        auto tile = map_area->GetTile(x, y);
        auto coord = Point{x, y};
        DrawGround(tile, coord);
        auto tile_symbols = std::make_shared<Tile>();
        tile_symbols->set_mob(tile->mob());
        tile_symbols->set_rid(rids_tile_symbols[x][y]);
        tile_symbols->set_tile_effect(tile->tile_effect());
        DrawTileSymbols(tile_symbols, coord);
      }
    }
    StopTileBatchDrawing();
    for (auto y = y_center - r; y <= y_center + r; y++) {
      for (auto x = x_center - r; x <= x_center + r; x++) {
        if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
          continue;
        auto dx = x - x_center;
        auto dy = y - y_center;
        if (dx * dx + dy * dy > r * r)
          continue;
        auto tile = map_area->GetTile(x, y);
        auto coord = Point{x, y};
        DrawObjects(tile, coord);
        DrawMob(tile, coord);
      }
    }
    DrawPlayer();
  }
}