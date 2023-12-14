#include "world_view_module_view.h"
#include "command/draw_ground.h"
#include "command/draw_mob.h"
#include "command/draw_objects.h"
#include "command/draw_player.h"
#include "command/draw_tile_symbols.h"
#include "conf/model/conf.h"
#include "core.render.models/view/command/start_models_batch_drawing.h"
#include "core.render.models/view/command/stop_models_batch_drawing.h"
#include "core.render.models/view/renderer_models_view.h"
#include "core.render/view/command/new_tile.h"
#include "core.render/view/command/set_tile_geometry.h"
#include "core.render/view/command/start_tile_batch_drawing.h"
#include "core.render/view/command/stop_tile_batch_drawing.h"
#include "world.actors/model/player.h"
#include "world.structure/model/world.h"
namespace Narradia
{
   WorldViewModuleView::WorldViewModuleView() {
      auto map_area = World::get()->curr_map_area();
      auto tile_size = kTileSize;
      for (auto x = 0; x < map_area->GetWidth(); x++) {
         rids_tiles.push_back(std::vector<RenderID>());
         rids_tile_symbols.push_back(std::vector<RenderID>());
         for (auto y = 0; y < map_area->GetHeight(); y++) {
            rids_tiles.at(x).push_back(NewTile());
            Vertex3F v0;
            Vertex3F v1;
            Vertex3F v2;
            Vertex3F v3;
            auto elev00 = map_area->GetTile(x, y)->elevation() * kElevAmount;
            auto elev10 = elev00;
            auto elev11 = elev00;
            auto elev01 = elev00;
            auto normal00 = map_area->GetTile(x, y)->normal();
            auto normal10 = normal00;
            auto normal11 = normal00;
            auto normal01 = normal00;
            auto color00 = *map_area->GetTile(x, y)->color();
            auto color10 = color00;
            auto color11 = color00;
            auto color01 = color00;
            auto coord10 = Point{x + 1, y};
            auto coord11 = Point{x + 1, y + 1};
            auto coord01 = Point{x, y + 1};
            if (map_area->IsInsideMap(coord10)) {
               elev10 = map_area->GetTile(coord10)->elevation() * kElevAmount;
               normal10 = map_area->GetTile(coord10)->normal();
               color10 = *map_area->GetTile(coord10)->color();
            }
            if (map_area->IsInsideMap(coord11)) {
               elev11 = map_area->GetTile(coord11)->elevation() * kElevAmount;
               normal11 = map_area->GetTile(coord11)->normal();
               color11 = *map_area->GetTile(coord11)->color();
            }
            if (map_area->IsInsideMap(coord01)) {
               elev01 = map_area->GetTile(coord01)->elevation() * kElevAmount;
               normal01 = map_area->GetTile(coord01)->normal();
               color01 = *map_area->GetTile(coord01)->color();
            }
            v0.position = {x * tile_size, elev00, y * tile_size};
            v1.position = {x * tile_size + tile_size, elev10, y * tile_size};
            v2.position = {x * tile_size + tile_size, elev11, y * tile_size + tile_size};
            v3.position = {x * tile_size, elev01, y * tile_size + tile_size};
            v0.uv = {0.0f, 0.0f};
            v1.uv = {1.0f, 0.0f};
            v2.uv = {1.0f, 1.0f};
            v3.uv = {0.0f, 1.0f};
            v0.color = color00;
            v1.color = color10;
            v2.color = color11;
            v3.color = color01;
            SetTileGeometry(
                rids_tiles[x][y], v0, v1, v2, v3, normal00, normal10, normal11, normal01);
            map_area->GetTile(x, y)->set_rid(rids_tiles[x][y]);
            rids_tile_symbols.at(x).push_back(NewTile());
            v0.position.y += kTinyDistance * kTileSize;
            v1.position.y += kTinyDistance * kTileSize;
            v2.position.y += kTinyDistance * kTileSize;
            v3.position.y += kTinyDistance * kTileSize;
            v0.color = Colors::white;
            v1.color = Colors::white;
            v2.color = Colors::white;
            v3.color = Colors::white;
            SetTileGeometry(
                rids_tile_symbols[x][y], v0, v1, v2, v3, normal00, normal10, normal11, normal01);
         }
      }
   }

   void WorldViewModuleView::Render() {
      auto map_area = World::get()->curr_map_area();
      auto player_pos = Player::get()->position();
      auto r = 30;
      auto x_center = static_cast<int>(player_pos.x);
      auto y_center = static_cast<int>(player_pos.z);
      StartTileBatchDrawing();
      for (auto y = y_center - r; y <= y_center + r; y++) {
         for (auto x = x_center - r; x <= x_center + r; x++) {
            if (x < 0 || y < 0 || x >= map_area->GetWidth() || y >= map_area->GetHeight())
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
      StartModelsBatchDrawing();
      for (auto y = y_center - r; y <= y_center + r; y++) {
         for (auto x = x_center - r; x <= x_center + r; x++) {
            if (x < 0 || y < 0 || x >= map_area->GetWidth() || y >= map_area->GetHeight())
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
      StopModelsBatchDrawing();
   }
}
