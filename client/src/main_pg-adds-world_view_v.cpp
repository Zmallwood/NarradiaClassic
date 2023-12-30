#if 1
#include "main_pg-adds-world_view_v.h"
#include "actors.h"
#include "conf.h"
#include "core.h"
#include "main_pg-adds-visual.h"
#include "rend_models_v.h"
#include "rend_tiles_v.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   WorldViewAddV::WorldViewAddV(bool simplified_ground)
       : simplified_ground_(simplified_ground) {
      InitCurrWorldArea();
   }
   void WorldViewAddV::InitCurrWorldArea() {
      auto world_area = World::get()->CurrWorldArea();
      auto curr_map_loc = Player::get()->world_location();
      auto tile_size = kTileSize;
      auto map_offset_x = curr_map_loc.x * world_area->GetWidth() * tile_size;
      auto map_offset_y = curr_map_loc.y * world_area->GetHeight() * tile_size;
      auto inc = 1;

      if (simplified_ground_)
         inc = kGroundSimpleK;

      class TileSquare {
        public:
         TileSquare(int x, int y) {
            coords._00 = {x, y};
            coords._10 = {x + 1, y};
            coords._11 = {x + 1, y + 1};
            coords._01 = {x, y + 1};
         }

         Square<Point> coords;
      };

      for (auto x = 0; x < world_area->GetWidth(); x += inc) {
         rids_tiles.push_back(std::vector<RenderID>());
         rids_tile_symbols.push_back(std::vector<RenderID>());

         for (auto y = 0; y < world_area->GetHeight(); y += inc) {
            rids_tiles.at(x / inc).push_back(NewTile());
            auto t_square = TileSquare(x, y);
            Square<Vertex3F> verts;
            Square<float> elevs;
            Square<Color> colors;
            elevs.SetAll(world_area->GetTile(x, y)->elevation() * kElevAmount);
            colors.SetAll(*world_area->GetTile(x, y)->color());

            verts._00.normal = world_area->GetTile(x, y)->normal();

            if (world_area->IsInsideMap(t_square.coords._10)) {
               auto tile = world_area->GetTile(t_square.coords._10);
               elevs._10 = tile->elevation() * kElevAmount;
               verts._10.normal = tile->normal();
               colors._10 = *tile->color();
            }

            if (world_area->IsInsideMap(t_square.coords._11)) {
               auto tile = world_area->GetTile(t_square.coords._11);
               elevs._11 = tile->elevation() * kElevAmount;
               verts._11.normal = tile->normal();
               colors._11 = *tile->color();
            }

            if (world_area->IsInsideMap(t_square.coords._01)) {
               auto tile = world_area->GetTile(t_square.coords._01);
               elevs._01 = tile->elevation() * kElevAmount;
               verts._01.normal = tile->normal();
               colors._01 = *tile->color();
            }

            auto tile_size_side = tile_size;

            if (simplified_ground_)
               tile_size_side *= kGroundSimpleK;

            verts._00.pos = {map_offset_x + x * tile_size, elevs._00, map_offset_y + y * tile_size};
            verts._10.pos = {
                map_offset_x + x * tile_size + tile_size_side, elevs._10,
                map_offset_y + y * tile_size};
            verts._11.pos = {
                map_offset_x + x * tile_size + tile_size_side, elevs._11,
                map_offset_y + y * tile_size + tile_size_side};
            verts._01.pos = {
                map_offset_x + x * tile_size, elevs._01,
                map_offset_y + y * tile_size + tile_size_side};

            verts._00.uv = {0.0f, 0.0f};
            verts._10.uv = {1.0f, 0.0f};
            verts._11.uv = {1.0f, 1.0f};
            verts._01.uv = {0.0f, 1.0f};

            verts._00.color = colors._00;
            verts._10.color = colors._10;
            verts._11.color = colors._11;
            verts._01.color = colors._01;

            SetTileGeometry(rids_tiles[x / inc][y / inc], verts);

            world_area->GetTile(x, y)->set_rid(rids_tiles[x / inc][y / inc]);

            rids_tile_symbols.at(x / inc).push_back(NewTile());

            verts._00.pos.y += kTinyDistance * kTileSize;
            verts._10.pos.y += kTinyDistance * kTileSize;
            verts._11.pos.y += kTinyDistance * kTileSize;
            verts._01.pos.y += kTinyDistance * kTileSize;

            SetTileGeometry(rids_tile_symbols[x / inc][y / inc], verts);
         }
      }
   }
   void WorldViewAddV::Render() {
      try {
         auto map_area = World::get()->CurrWorldArea();
         auto world_loc = Player::get()->world_location();

         auto loc_n = world_loc.Translate(0, -1);
         auto loc_ne = world_loc.Translate(1, -1);
         auto loc_e = world_loc.Translate(1, 0);
         auto loc_se = world_loc.Translate(1, 1);
         auto loc_s = world_loc.Translate(0, 1);
         auto loc_sw = world_loc.Translate(-1, 1);
         auto loc_w = world_loc.Translate(-1, 0);
         auto loc_nw = world_loc.Translate(-1, -1);

         std::shared_ptr<WorldArea> map_area_n = World::get()->WorldAreaAt(loc_n);
         std::shared_ptr<WorldArea> map_area_ne = World::get()->WorldAreaAt(loc_ne);
         std::shared_ptr<WorldArea> map_area_e = World::get()->WorldAreaAt(loc_e);
         std::shared_ptr<WorldArea> map_area_se = World::get()->WorldAreaAt(loc_se);
         std::shared_ptr<WorldArea> map_area_s = World::get()->WorldAreaAt(loc_s);
         std::shared_ptr<WorldArea> map_area_sw = World::get()->WorldAreaAt(loc_sw);
         std::shared_ptr<WorldArea> map_area_w = World::get()->WorldAreaAt(loc_w);
         std::shared_ptr<WorldArea> map_area_nw = World::get()->WorldAreaAt(loc_nw);

         auto player_pos = Player::get()->position();
         auto r = render_distance_;
         auto x_center = static_cast<int>(player_pos.x);
         auto y_center = static_cast<int>(player_pos.z);
         auto inc = 1;

         if (simplified_ground_)
            inc = kGroundSimpleK;

         StartTileBatchDrawing();

         for (auto y = y_center - r - 1; y <= y_center + r + 1; y++) {
            for (auto x = x_center - r - 1; x <= x_center + r + 1; x++) {
               auto dx = x - x_center;
               auto dy = y - y_center;

               if (dx * dx + dy * dy > r * r)
                  continue;

               if (simplified_ground_) {
                  if (x % kGroundSimpleK != 0 || y % kGroundSimpleK != 0)
                     continue;
               }

               if (x < 0 || y < 0 || x >= map_area->GetWidth() || y >= map_area->GetHeight()) {
                  if (simplified_ground_)
                     continue;

                  // West
                  if (x < 0 && y >= 0 && y < map_area->GetHeight()) {
                     if (map_area_w) {
                        auto tile = map_area_w->GetTile(map_area->GetWidth() + x, y);
                        if (tile) {
                           auto rid = tile->rid();
                           if (!rid) {
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

                              if (map_area_w->IsInsideMap(coord10)) {
                                 elev10 = map_area_w->GetTile(coord10)->elevation() * kElevAmount;
                                 normal10 = map_area_w->GetTile(coord10)->normal();
                                 color10 = *map_area_w->GetTile(coord10)->color();
                              }

                              if (map_area_w->IsInsideMap(coord11)) {
                                 elev11 = map_area_w->GetTile(coord11)->elevation() * kElevAmount;
                                 normal11 = map_area_w->GetTile(coord11)->normal();
                                 color11 = *map_area_w->GetTile(coord11)->color();
                              }

                              if (map_area_w->IsInsideMap(coord01)) {
                                 elev01 = map_area_w->GetTile(coord01)->elevation() * kElevAmount;
                                 normal01 = map_area_w->GetTile(coord01)->normal();
                                 color01 = *map_area_w->GetTile(coord01)->color();
                              }

                              auto tile_size_side = tile_size;

                              if (simplified_ground_)
                                 tile_size_side *= kGroundSimpleK;
                              v0.pos = {
                                  map_offset_x + x * tile_size, elev00,
                                  map_offset_y + y * tile_size};
                              v1.pos = {
                                  map_offset_x + x * tile_size + tile_size_side, elev10,
                                  map_offset_y + y * tile_size};
                              v2.pos = {
                                  map_offset_x + x * tile_size + tile_size_side, elev11,
                                  map_offset_y + y * tile_size + tile_size_side};
                              v3.pos = {
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

                              Square<Vertex3F> verts;
                              Square<Point3F> norms;

                              verts._00 = v0;
                              verts._10 = v1;
                              verts._11 = v2;
                              verts._01 = v3;

                              verts._00.normal = normal00;
                              verts._10.normal = normal10;
                              verts._11.normal = normal11;
                              verts._01.normal = normal01;

                              SetTileGeometry(rid, verts);
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
               else {
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
               // DrawMob(tile, coord);
            }
         }

         DrawPlayer();
         StopModelsBatchDrawing();
      }
      catch (std::exception &e) {
         Console::get()->Print("Exception in WorldViewAdd::Render: " + std::string(e.what()));
      }
   }
   void WorldViewAddV::DrawGround(std::shared_ptr<Tile> tile, Point coord) {
      auto ground = tile->ground();
      if (ground == "GroundWater") {
         auto anim_index = ((SDL_GetTicks() + coord.x * coord.y) % 900) / 300;
         if (anim_index > 0)
            ground = "GroundWater_" + std::to_string(anim_index);
      }
      if (ground == "GroundGrass") {
         auto vary_index = (coord.x * coord.y) % 3;
         ground = "GroundGrass_" + std::to_string(vary_index);
      }
      // std::cout << ground << std::endl;
      DrawTile(ground, tile->rid());
   }
   void WorldViewAddV::DrawObjects(std::shared_ptr<Tile> tile, Point coord) {
      if (tile->object()) {
         auto map_area = World::get()->CurrWorldArea();
         auto curr_map_location = Player::get()->world_location();
         auto tile_size = kTileSize;
         auto map_offset_x = curr_map_location.x * map_area->GetWidth() * tile_size;
         auto map_offset_y = curr_map_location.y * map_area->GetHeight() * tile_size;
         auto pos =
             Point3F{coord.x * kTileSize, CalcTileAverageElevation(coord), coord.y * kTileSize}
                 .Translate(0.5f, 0.0f, 0.5f)
                 .Translate(map_offset_x, 0.0f, map_offset_y);
         auto model_rotation = 360.0f * ((coord.x * coord.y) % 10) / 10.0f;
         auto model_scaling = 0.6f * ObjectsConf::get()->GetModelScaling(tile->object()->type());
         DrawModel(
             tile->object()->type(), SDL_GetTicks() + coord.x * coord.y * 10, pos, model_rotation,
             model_scaling);
      }
   }
   void WorldViewAddV::DrawPlayer() {
      auto map_area = World::get()->CurrWorldArea();
      auto curr_map_location = Player::get()->world_location();
      auto tile_size = kTileSize;
      auto map_offset_x = curr_map_location.x * map_area->GetWidth() * tile_size;
      auto map_offset_y = curr_map_location.y * map_area->GetHeight() * tile_size;
      auto player_space_coord = Player::get()->position().Multiply(kTileSize);
      player_space_coord.x += map_offset_x;
      player_space_coord.z += map_offset_y;
      auto player_map_coord = Player::get()->position().GetXZ().ToIntPoint();
      auto tile_average_elevation = CalcTileAverageElevation(player_map_coord);
      player_space_coord.y += tile_average_elevation;
      auto ms_anim_time = 0.0f;
      if (Player::get()->IsMoving())
         ms_anim_time = SDL_GetTicks() * 2;
      DrawModel(
          "Player2", ms_anim_time, player_space_coord, Player::get()->facing_angle_deg() + 180.0f,
          0.6f);
   }
   void WorldViewAddV::DrawTileSymbols(std::shared_ptr<Tile> tile, Point coord) {
      auto player_pos = Player::get()->position().GetXZ().ToIntPoint();
      if (SDL_GetTicks() <
              Player::get()->ticks_ulti_skill_start() + Player::get()->ulti_skill_duration() &&
          Player::get()->ticks_ulti_skill_start() != 0 && coord.x == player_pos.x &&
          coord.y == player_pos.y) {
         DrawTile("TilePlayerUltiSkill", tile->rid());
      }
      else if (SDL_GetTicks() < tile->tile_effect().ticks_started + 800) {
         DrawTile(tile->tile_effect().type, tile->rid());
      }
      else {
         auto hovered_tile = TileHoveringAdd::get()->hovered_tile();
         if (hovered_tile.x == coord.x && hovered_tile.y == coord.y) {
            DrawTile("TileHovered", tile->rid());
         }
      }
   }
}
