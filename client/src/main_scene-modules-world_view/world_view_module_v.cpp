#if 1
#include "world_view_module_v.h"
#include "render/cmd_v/new_tile.h"
#include "cmd_v/draw_ground.h"
#include "cmd_v/draw_mob.h"
#include "cmd_v/draw_objects.h"
#include "cmd_v/draw_player.h"
#include "cmd_v/draw_tile_symbols.h"
#include "conf.h"
#include "render-models/cmd_v/start_models_batch_drawing.h"
#include "render-models/cmd_v/stop_models_batch_drawing.h"
#include "render-models/renderer_models_v.h"
#include "render/cmd_v/set_tile_geometry.h"
#include "render/cmd_v/start_tile_batch_drawing.h"
#include "render/cmd_v/stop_tile_batch_drawing.h"
#include "actors.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   WorldViewModuleV::WorldViewModuleV(bool simplified_ground)
       : simplified_ground_(simplified_ground)
   {
      auto map_area = World::get()->CurrMapArea();
      auto curr_map_location = Player::get()->world_location();
      auto tile_size = kTileSize;
      auto map_offset_x = curr_map_location.x * map_area->GetWidth() * tile_size;
      auto map_offset_y = curr_map_location.y * map_area->GetHeight() * tile_size;
      auto inc = 1;

      if (simplified_ground_)
         inc = kGroundSimpleK;

      for (auto x = 0; x < map_area->GetWidth(); x += inc)
      {
         rids_tiles.push_back(std::vector<RenderID>());
         rids_tile_symbols.push_back(std::vector<RenderID>());

         for (auto y = 0; y < map_area->GetHeight(); y += inc)
         {
            rids_tiles.at(x / inc).push_back(NewTile());
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

            if (map_area->IsInsideMap(coord10))
            {
               elev10 = map_area->GetTile(coord10)->elevation() * kElevAmount;
               normal10 = map_area->GetTile(coord10)->normal();
               color10 = *map_area->GetTile(coord10)->color();
            }

            if (map_area->IsInsideMap(coord11))
            {
               elev11 = map_area->GetTile(coord11)->elevation() * kElevAmount;
               normal11 = map_area->GetTile(coord11)->normal();
               color11 = *map_area->GetTile(coord11)->color();
            }

            if (map_area->IsInsideMap(coord01))
            {
               elev01 = map_area->GetTile(coord01)->elevation() * kElevAmount;
               normal01 = map_area->GetTile(coord01)->normal();
               color01 = *map_area->GetTile(coord01)->color();
            }

            auto tile_size_side = tile_size;

            if (simplified_ground_)
               tile_size_side *= kGroundSimpleK;

            v0.position = {map_offset_x + x * tile_size, elev00, map_offset_y + y * tile_size};
            v1.position = {
                map_offset_x + x * tile_size + tile_size_side, elev10,
                map_offset_y + y * tile_size};
            v2.position = {
                map_offset_x + x * tile_size + tile_size_side, elev11,
                map_offset_y + y * tile_size + tile_size_side};
            v3.position = {
                map_offset_x + x * tile_size, elev01,
                map_offset_y + y * tile_size + tile_size_side};

            v0.uv = {0.0f, 0.0f};
            v1.uv = {1.0f, 0.0f};
            v2.uv = {1.0f, 1.0f};
            v3.uv = {0.0f, 1.0f};

            v0.color = color00;
            v1.color = color10;
            v2.color = color11;
            v3.color = color01;

            SetTileGeometry(
                rids_tiles[x / inc][y / inc], v0, v1, v2, v3, normal00, normal10, normal11,
                normal01);

            map_area->GetTile(x, y)->set_rid(rids_tiles[x / inc][y / inc]);

            rids_tile_symbols.at(x / inc).push_back(NewTile());

            v0.position.y += kTinyDistance * kTileSize;
            v1.position.y += kTinyDistance * kTileSize;
            v2.position.y += kTinyDistance * kTileSize;
            v3.position.y += kTinyDistance * kTileSize;

            v0.color = Colors::white;
            v1.color = Colors::white;
            v2.color = Colors::white;
            v3.color = Colors::white;

            SetTileGeometry(
                rids_tile_symbols[x / inc][y / inc], v0, v1, v2, v3, normal00, normal10, normal11,
                normal01);
         }
      }
   }
   void WorldViewModuleV::Render()
   {
      auto map_area = World::get()->CurrMapArea();
      auto world_loc = Player::get()->world_location();

      auto loc_n = world_loc.Translate(0, -1);
      auto loc_ne = world_loc.Translate(1, -1);
      auto loc_e = world_loc.Translate(1, 0);
      auto loc_se = world_loc.Translate(1, 1);
      auto loc_s = world_loc.Translate(0, 1);
      auto loc_sw = world_loc.Translate(-1, 1);
      auto loc_w = world_loc.Translate(-1, 0);
      auto loc_nw = world_loc.Translate(-1, -1);

      std::shared_ptr<MapArea> map_area_n = World::get()->MapAreaAt(loc_n);
      std::shared_ptr<MapArea> map_area_ne = World::get()->MapAreaAt(loc_ne);
      std::shared_ptr<MapArea> map_area_e = World::get()->MapAreaAt(loc_e);
      std::shared_ptr<MapArea> map_area_se = World::get()->MapAreaAt(loc_se);
      std::shared_ptr<MapArea> map_area_s = World::get()->MapAreaAt(loc_s);
      std::shared_ptr<MapArea> map_area_sw = World::get()->MapAreaAt(loc_sw);
      std::shared_ptr<MapArea> map_area_w = World::get()->MapAreaAt(loc_w);
      std::shared_ptr<MapArea> map_area_nw = World::get()->MapAreaAt(loc_nw);

      auto player_pos = Player::get()->position();
      auto r = render_distance_;
      auto x_center = static_cast<int>(player_pos.x);
      auto y_center = static_cast<int>(player_pos.z);
      auto inc = 1;

      if (simplified_ground_)
         inc = kGroundSimpleK;

      StartTileBatchDrawing();

      for (auto y = y_center - r - 1; y <= y_center + r + 1; y++)
      {
         for (auto x = x_center - r - 1; x <= x_center + r + 1; x++)
         {
            auto dx = x - x_center;
            auto dy = y - y_center;

            if (dx * dx + dy * dy > r * r)
               continue;

            if (simplified_ground_)
            {
               if (x % kGroundSimpleK != 0 || y % kGroundSimpleK != 0)
                  continue;
            }

            if (x < 0 || y < 0 || x >= map_area->GetWidth() || y >= map_area->GetHeight())
            {
               if (simplified_ground_)
                  continue;

               // West
               if (x < 0 && y >= 0 && y < map_area->GetHeight())
               {
                  if (map_area_w)
                  {
                     auto tile = map_area_w->GetTile(map_area->GetWidth() + x, y);
                     if (tile)
                     {
                        auto rid = tile->rid();
                        if (!rid)
                        {
                           rid = NewTile();
                           auto curr_map_location = Player::get()->world_location();
                           auto tile_size = kTileSize;
                           auto map_offset_x =
                               curr_map_location.x * map_area->GetWidth() * tile_size;
                           auto map_offset_y =
                               curr_map_location.y * map_area->GetHeight() * tile_size;
                           int x_orig = x;
                           int y_orig = y;
                           int x;
                           int y;
                           x = map_area->GetWidth() + x_orig;
                           y = y_orig;
                           auto map_offset_x_orig = map_offset_x;
                           auto map_offset_y_orig = map_offset_y;
                           map_offset_x -= map_area->GetWidth() * kTileSize;
                           Vertex3F v0;
                           Vertex3F v1;
                           Vertex3F v2;
                           Vertex3F v3;
                           auto elev00 = map_area_w->GetTile(x, y)->elevation() * kElevAmount;
                           auto elev10 = elev00;
                           auto elev11 = elev00;
                           auto elev01 = elev00;
                           auto normal00 = map_area_w->GetTile(x, y)->normal();
                           auto normal10 = normal00;
                           auto normal11 = normal00;
                           auto normal01 = normal00;
                           auto color00 = *map_area_w->GetTile(x, y)->color();
                           auto color10 = color00;
                           auto color11 = color00;
                           auto color01 = color00;
                           auto coord10 = Point{x + 1, y};
                           auto coord11 = Point{x + 1, y + 1};
                           auto coord01 = Point{x, y + 1};

                           if (map_area_w->IsInsideMap(coord10))
                           {
                              elev10 = map_area_w->GetTile(coord10)->elevation() * kElevAmount;
                              normal10 = map_area_w->GetTile(coord10)->normal();
                              color10 = *map_area_w->GetTile(coord10)->color();
                           }

                           if (map_area_w->IsInsideMap(coord11))
                           {
                              elev11 = map_area_w->GetTile(coord11)->elevation() * kElevAmount;
                              normal11 = map_area_w->GetTile(coord11)->normal();
                              color11 = *map_area_w->GetTile(coord11)->color();
                           }

                           if (map_area_w->IsInsideMap(coord01))
                           {
                              elev01 = map_area_w->GetTile(coord01)->elevation() * kElevAmount;
                              normal01 = map_area_w->GetTile(coord01)->normal();
                              color01 = *map_area_w->GetTile(coord01)->color();
                           }

                           auto tile_size_side = tile_size;

                           if (simplified_ground_)
                              tile_size_side *= kGroundSimpleK;
                           v0.position = {
                               map_offset_x + x * tile_size, elev00, map_offset_y + y * tile_size};
                           v1.position = {
                               map_offset_x + x * tile_size + tile_size_side, elev10,
                               map_offset_y + y * tile_size};
                           v2.position = {
                               map_offset_x + x * tile_size + tile_size_side, elev11,
                               map_offset_y + y * tile_size + tile_size_side};
                           v3.position = {
                               map_offset_x + x * tile_size, elev01,
                               map_offset_y + y * tile_size + tile_size_side};

                           v0.uv = {0.0f, 0.0f};
                           v1.uv = {1.0f, 0.0f};
                           v2.uv = {1.0f, 1.0f};
                           v3.uv = {0.0f, 1.0f};

                           v0.color = color00;
                           v1.color = color10;
                           v2.color = color11;
                           v3.color = color01;

                           SetTileGeometry(
                               rid, v0, v1, v2, v3, normal00, normal10, normal11, normal01);
                           map_area_w->GetTile(x, y)->set_rid(rid);
                        }

                        auto coord = Point{x, y};

                        DrawGround(tile, coord);

                        //                        auto tile_symbols =
                        //                        std::make_shared<Tile>();
                        //                        tile_symbols->set_mob(tile->mob());
                        //                        tile_symbols->set_rid(rids_tile_symbols[x
                        //                        / inc][y / inc]);
                        //                        tile_symbols->set_tile_effect(tile->tile_effect());
                        //                        DrawTileSymbols(tile_symbols,
                        //                        coord);
                     }
                  }
               }
            }
            else
            {
               auto tile = map_area->GetTile(x, y);
               auto coord = Point{x, y};
               DrawGround(tile, coord);
               auto tile_symbols = std::make_shared<Tile>();
               tile_symbols->set_mob(tile->mob());
               tile_symbols->set_rid(rids_tile_symbols[x / inc][y / inc]);
               tile_symbols->set_tile_effect(tile->tile_effect());
               DrawTileSymbols(tile_symbols, coord);
            }
         }
      }

      StopTileBatchDrawing();
      StartModelsBatchDrawing();

      for (auto y = y_center - r; y <= y_center + r; y++)
      {
         for (auto x = x_center - r; x <= x_center + r; x++)
         {
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
   void WorldViewModuleV::UnloadTile(int x, int y)
   {
   }
   void WorldViewModuleV::LoadTile(int x, int y)
   {
   }
}