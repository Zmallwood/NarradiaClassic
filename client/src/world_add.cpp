#if 1
#include "world_add.h"
#include "adds.h"
#include "assets.h"
#include "calc.h"
#include "conf.h"
#include "core.h"
#include "hero.h"
#include "rend-core.h"
#include "rend_grnd.h"
#include "rend_models.h"
#include "world.h"
#endif

namespace Narradia
{
// Model
#if 1
   // WorldModele
#if 1
   WorldAdd::WorldAdd() {
   }

   void WorldAdd::UpdateGameLogic() {

      Camera::get()->UpdateGameLogic();
   }
#endif

   // Camera
#if 1
   void Camera::UpdateGameLogic() {

      SetPerspMat();
      SetViewMat();
   }

   void Camera::SetPerspMat() {

      auto fov_rads = glm::radians(used_fov_ / 2);
      auto aspect = 1600.0f / 900.0f;
      auto z_near = 0.1f;
      auto z_far = 3000.0f;
      auto new_persp_mat = glm::perspective(fov_rads, aspect, z_near, z_far);
      CameraGL::get()->set_persp_matrix(new_persp_mat);
   }

   void Camera::SetViewMat() {

      auto player_pos = Hero::get()->pos().Multiply(kTileSize);
      auto curr_world_loc = Hero::get()->world_location();
      auto t_sz = kTileSize;
      auto curr_wa = World::get()->CurrWorldArea();
      auto map_offs_x = curr_world_loc.x * curr_wa->Width() * t_sz;
      auto map_offs_y = curr_world_loc.y * curr_wa->Height() * t_sz;
      auto look_from = GetCameraPos();
      look_from = look_from.Translate(map_offs_x, 0.0f, map_offs_y);
      auto player_avg_elev = CalcTileAverageElevation(
          Hero::get()->pos().GetXZ().ToIntPoint(), Hero::get()->world_location());
      auto look_at = player_pos.Translate(0.0f, player_avg_elev, 0.0f);
      look_at = look_at.Translate(map_offs_x, 0.0f, map_offs_y);
      auto new_view_matrix = glm::lookAt(
          glm::vec3(look_from.x, look_from.y, look_from.z),
          glm::vec3(look_at.x, look_at.y, look_at.z), glm::vec3(0.0, 1.0, 0.0));
      CameraGL::get()->set_view_matrix(new_view_matrix);
   }

   Point3F Camera::GetCameraPos() {

      auto player = Hero::get();
      float player_elev;
      {
         auto player_position = player->pos().GetXZ();
         auto curr_wa = World::get()->CurrWorldArea();
         auto tile_coord = player_position.ToIntPoint();
         auto tile = curr_wa->GetTile(tile_coord);
         float elev00 = static_cast<float>(tile->elevation());
         float elev10 = elev00;
         float elev11 = elev00;
         float elev01 = elev00;
         {
            auto coord10 = tile_coord.Translate(1, 0);
            auto coord11 = tile_coord.Translate(1, 1);
            auto coord01 = tile_coord.Translate(0, 1);

            if (curr_wa->IsInsideMap(coord10))
               elev10 = curr_wa->GetTile(coord10)->elevation();

            if (curr_wa->IsInsideMap(coord11))
               elev11 = curr_wa->GetTile(coord11)->elevation();

            if (curr_wa->IsInsideMap(coord01))
               elev01 = curr_wa->GetTile(coord01)->elevation();
         }
         {
            auto tile_avg_elev = (elev00 + elev10 + elev01 + elev11) / 4.0f;
            auto player_tile_dx = player_position.x - static_cast<int>(player_position.x) - 0.5f;
            auto player_tile_dy = player_position.y - static_cast<int>(player_position.y) - 0.5f;
            auto elev_dx = ((elev10 - elev00) + (elev11 - elev01)) / 2.0f;
            auto elev_dy = ((elev01 - elev00) + (elev11 - elev10)) / 2.0f;
            player_elev = tile_avg_elev + player_tile_dx * elev_dx + player_tile_dy * elev_dy;
         }
      }
      Point3F result;
      {
         auto elev_amount = kElevAmount;
         auto player_position_no_elevation = player->pos().Multiply(kTileSize);
         player_position_no_elevation.y = 0.0f;
         auto used_vertical_angle = vertical_angle_deg_;
         auto used_camera_distance = camera_distance_ * 2.0f;
         auto dz_unrotated = CosDeg(used_vertical_angle) * used_camera_distance;
         auto hypotenuse = dz_unrotated;
         auto dx =
             SinDeg(horizontal_angle_deg_) * hypotenuse - 3.0f * SinDeg(horizontal_angle_deg_);
         auto dz =
             CosDeg(horizontal_angle_deg_) * hypotenuse - 3.0f * CosDeg(horizontal_angle_deg_);
         auto dy = SinDeg(used_vertical_angle) * used_camera_distance * 3.0f;
         auto player_average_elevation = CalcTileAverageElevation(
             Hero::get()->pos().GetXZ().ToIntPoint(), Hero::get()->world_location());
         result = player_position_no_elevation.Translate(dx, dy + player_average_elevation, dz);
      }
      return result.Translate(0.0f, camera_height_ * 2.0f, 0.0f);
   }
#endif
#endif

// View
#if 1
   WorldAddV::WorldAddV(bool simplified_ground)
       : simplified_ground_(simplified_ground) {

      InitCurrWorldArea();
   }

   void WorldAddV::InitCurrWorldArea() {

      auto wa = World::get()->CurrWorldArea();
      auto curr_map_loc = Hero::get()->world_location();
      auto t_sz = kTileSize;
      auto map_offset_x = curr_map_loc.x * wa->Width() * t_sz;
      auto map_offset_y = curr_map_loc.y * wa->Height() * t_sz;
      auto inc = 1;

      if (simplified_ground_)
         inc = kGroundSimpleK;

      for (auto x = 0; x < wa->Width(); x += inc) {

         rids_tiles.push_back(Vec<RenderID>());
         rids_tile_symbols.push_back(Vec<RenderID>());

         for (auto y = 0; y < wa->Height(); y += inc) {

            rids_tiles.at(x / inc).push_back(NewTile());
            auto t_square = TileSquare(x, y);
            Square<Vertex3F> verts;
            Square<float> elevs;
            Square<Color> colors;
            elevs.SetAll(wa->GetTile(x, y)->elevation() * kElevAmount);
            colors.SetAll(*wa->GetTile(x, y)->color());

            verts._00.normal = wa->GetTile(x, y)->normal();

            if (wa->IsInsideMap(t_square.coords._10)) {
               auto tile = wa->GetTile(t_square.coords._10);
               elevs._10 = tile->elevation() * kElevAmount;
               verts._10.normal = tile->normal();
               colors._10 = *tile->color();
            }

            if (wa->IsInsideMap(t_square.coords._11)) {
               auto tile = wa->GetTile(t_square.coords._11);
               elevs._11 = tile->elevation() * kElevAmount;
               verts._11.normal = tile->normal();
               colors._11 = *tile->color();
            }

            if (wa->IsInsideMap(t_square.coords._01)) {
               auto tile = wa->GetTile(t_square.coords._01);
               elevs._01 = tile->elevation() * kElevAmount;
               verts._01.normal = tile->normal();
               colors._01 = *tile->color();
            }

            auto t_sz_side = t_sz;

            if (simplified_ground_)
               t_sz_side *= kGroundSimpleK;

            verts._00.pos = {map_offset_x + x * t_sz, elevs._00, map_offset_y + y * t_sz};
            verts._10.pos = {
                map_offset_x + x * t_sz + t_sz_side, elevs._10, map_offset_y + y * t_sz};
            verts._11.pos = {
                map_offset_x + x * t_sz + t_sz_side, elevs._11,
                map_offset_y + y * t_sz + t_sz_side};
            verts._01.pos = {
                map_offset_x + x * t_sz, elevs._01, map_offset_y + y * t_sz + t_sz_side};

            verts._00.uv = {0.0f, 0.0f};
            verts._10.uv = {1.0f, 0.0f};
            verts._11.uv = {1.0f, 1.0f};
            verts._01.uv = {0.0f, 1.0f};

            verts._00.color = colors._00;
            verts._10.color = colors._10;
            verts._11.color = colors._11;
            verts._01.color = colors._01;

            SetTileGeom(rids_tiles[x / inc][y / inc], verts);

            wa->GetTile(x, y)->set_rid(rids_tiles[x / inc][y / inc]);

            rids_tile_symbols.at(x / inc).push_back(NewTile());

            verts._00.pos.y += kTinyDistance * t_sz;
            verts._10.pos.y += kTinyDistance * t_sz;
            verts._11.pos.y += kTinyDistance * t_sz;
            verts._01.pos.y += kTinyDistance * t_sz;

            SetTileGeom(rids_tile_symbols[x / inc][y / inc], verts);
         }
      }
   }

   void WorldAddV::Render() {

      try {

         DrawAllGround();
         DrawAllModels();
      }
      catch (Exception &e) {

         Console::get()->Print("Exception in WorldViewAdd::Render: " + String(e.what()));
      }
   }

   void WorldAddV::DrawAllGround() {

      auto curr_wa = World::get()->CurrWorldArea();
      auto world_loc = Hero::get()->world_location();

      auto loc_n = world_loc.Translate(0, -1);
      auto loc_ne = world_loc.Translate(1, -1);
      auto loc_e = world_loc.Translate(1, 0);
      auto loc_se = world_loc.Translate(1, 1);
      auto loc_s = world_loc.Translate(0, 1);
      auto loc_sw = world_loc.Translate(-1, 1);
      auto loc_nw = world_loc.Translate(-1, -1);

      auto wa_n = World::get()->WorldAreaAt(loc_n);
      auto wa_ne = World::get()->WorldAreaAt(loc_ne);
      auto wa_e = World::get()->WorldAreaAt(loc_e);
      auto wa_se = World::get()->WorldAreaAt(loc_se);
      auto wa_s = World::get()->WorldAreaAt(loc_s);
      auto wa_sw = World::get()->WorldAreaAt(loc_sw);
      auto wa_nw = World::get()->WorldAreaAt(loc_nw);

      auto r = render_distance_;
      auto x_center = static_cast<int>(Hero::get()->pos().x);
      auto y_center = static_cast<int>(Hero::get()->pos().z);
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

            if (x < 0 || y < 0 || x >= curr_wa->Width() || y >= curr_wa->Height()) {

               if (simplified_ground_)
                  continue;

               // West
               if (x < 0 && y >= 0 && y < curr_wa->Height()) {

                  int x_orig = x;
                  int y_orig = y;
                  int x;
                  int y;
                  x = x_orig + curr_wa->Width();
                  y = y_orig;
                  DrawGroundTileOutsideWorldArea(x, y, -1, 0);
               }
               // East
               else if (x >= curr_wa->Width() && y >= 0 && y < curr_wa->Height()) {

                  int x_orig = x;
                  int y_orig = y;
                  int x;
                  int y;
                  x = x_orig - curr_wa->Width();
                  y = y_orig;
                  DrawGroundTileOutsideWorldArea(x, y, 1, 0);
               }
               // North
               else if (x >= 0 && y < 0 && x < curr_wa->Width()) {

                  int x_orig = x;
                  int y_orig = y;
                  int x;
                  int y;
                  x = x_orig;
                  y = y_orig + curr_wa->Height();
                  DrawGroundTileOutsideWorldArea(x, y, 0, -1);
               }
               // South
               else if (x >= 0 && y >= curr_wa->Height() && x < curr_wa->Width()) {

                  int x_orig = x;
                  int y_orig = y;
                  int x;
                  int y;
                  x = x_orig;
                  y = y_orig - curr_wa->Height();
                  DrawGroundTileOutsideWorldArea(x, y, 0, 1);
               }
            }
            else {

               auto tile = curr_wa->GetTile(x, y);
               auto coord = Point{x, y};
               DrawGround(tile, coord);
               auto tile_symbols = MakeShared<Tile>();
               tile_symbols->set_mob(tile->mob());
               tile_symbols->set_rid(rids_tile_symbols[x / inc][y / inc]);
               tile_symbols->set_tile_effect(tile->tile_effect());
               DrawTileSymbols(tile_symbols, coord);
            }
         }
      }

      StopTileBatchDrawing();
   }

   void WorldAddV::DrawAllModels() {

      auto curr_wa = World::get()->CurrWorldArea();
      auto x_center = static_cast<int>(Hero::get()->pos().x);
      auto y_center = static_cast<int>(Hero::get()->pos().z);
      auto r = render_distance_;

      StartModelsBatchDrawing();

      for (auto y = y_center - r; y <= y_center + r; y++) {

         for (auto x = x_center - r; x <= x_center + r; x++) {

            auto dx = x - x_center;
            auto dy = y - y_center;

            if (dx * dx + dy * dy > r * r)
               continue;

            if (x < 0 || y < 0 || x >= curr_wa->Width() || y >= curr_wa->Height()) {

               // West
               if (x < 0 && y >= 0 && y < curr_wa->Height()) {

                  int x_orig = x;
                  int y_orig = y;
                  int x;
                  int y;
                  x = curr_wa->Width() + x_orig;
                  y = y_orig;
                  DrawModelsTileOutsideWorldArea(x, y, -1, 0);
               }
               // East
               else if (x >= curr_wa->Width() && y >= 0 && y < curr_wa->Height()) {

                  int x_orig = x;
                  int y_orig = y;
                  int x;
                  int y;
                  x = x_orig - curr_wa->Width();
                  y = y_orig;
                  DrawModelsTileOutsideWorldArea(x, y, 1, 0);
               }
               // North
               else if (x >= 0 && y < 0 && x < curr_wa->Width()) {
                  int x_orig = x;
                  int y_orig = y;
                  int x;
                  int y;
                  x = x_orig;
                  y = y_orig + curr_wa->Height();
                  DrawModelsTileOutsideWorldArea(x, y, 0, -1);
               }
               // South
               else if (x >= 0 && y >= curr_wa->Height() && x < curr_wa->Width()) {

                  int x_orig = x;
                  int y_orig = y;
                  int x;
                  int y;
                  x = x_orig;
                  y = y_orig - curr_wa->Height();
                  DrawModelsTileOutsideWorldArea(x, y, 0, 1);
               }
            }
            else {

               auto tile = curr_wa->GetTile(x, y);
               auto coord = Point{x, y};

               DrawObjects(tile, coord);
            }
         }
      }

      DrawPlayer();
      StopModelsBatchDrawing();
   }

   void WorldAddV::DrawGroundTileOutsideWorldArea(int x, int y, int dloc_x, int dloc_y) {

      auto curr_wa = World::get()->CurrWorldArea();
      auto world_loc = Hero::get()->world_location();
      auto loc = world_loc.Translate(dloc_x, dloc_y);
      auto wa = World::get()->WorldAreaAt(loc);

      if (wa) {

         if (wa->IsInsideMap({x, y})) {

            auto tile = wa->GetTile(x, y);

            if (tile) {

               auto rid = tile->rid();

               if (!rid) {

                  rid = NewTile();
                  auto curr_map_loc = Hero::get()->world_location();
                  auto t_sz = kTileSize;
                  auto map_offs_x = curr_map_loc.x * curr_wa->Width() * t_sz;
                  auto map_offs_y = curr_map_loc.y * curr_wa->Height() * t_sz;
                  auto map_offs_x_orig = map_offs_x;
                  auto map_offs_y_orig = map_offs_y;
                  map_offs_x += dloc_x * curr_wa->Width() * kTileSize;
                  map_offs_y += dloc_y * curr_wa->Height() * kTileSize;
                  Vertex3F v0;
                  Vertex3F v1;
                  Vertex3F v2;
                  Vertex3F v3;
                  auto elev00 = wa->GetTile(x, y)->elevation() * kElevAmount;
                  auto elev10 = elev00;
                  auto elev11 = elev00;
                  auto elev01 = elev00;
                  auto normal00 = wa->GetTile(x, y)->normal();
                  auto normal10 = normal00;
                  auto normal11 = normal00;
                  auto normal01 = normal00;
                  auto color00 = *wa->GetTile(x, y)->color();
                  auto color10 = color00;
                  auto color11 = color00;
                  auto color01 = color00;
                  auto coord10 = Point{x + 1, y};
                  auto coord11 = Point{x + 1, y + 1};
                  auto coord01 = Point{x, y + 1};

                  if (wa->IsInsideMap(coord10)) {

                     elev10 = wa->GetTile(coord10)->elevation() * kElevAmount;
                     normal10 = wa->GetTile(coord10)->normal();
                     color10 = *wa->GetTile(coord10)->color();
                  }

                  if (wa->IsInsideMap(coord11)) {

                     elev11 = wa->GetTile(coord11)->elevation() * kElevAmount;
                     normal11 = wa->GetTile(coord11)->normal();
                     color11 = *wa->GetTile(coord11)->color();
                  }

                  if (wa->IsInsideMap(coord01)) {

                     elev01 = wa->GetTile(coord01)->elevation() * kElevAmount;
                     normal01 = wa->GetTile(coord01)->normal();
                     color01 = *wa->GetTile(coord01)->color();
                  }

                  auto t_sz_side = t_sz;

                  if (simplified_ground_)
                     t_sz_side *= kGroundSimpleK;

                  v0.pos = {map_offs_x + x * t_sz, elev00, map_offs_y + y * t_sz};
                  v1.pos = {map_offs_x + x * t_sz + t_sz_side, elev10, map_offs_y + y * t_sz};
                  v2.pos = {
                      map_offs_x + x * t_sz + t_sz_side, elev11, map_offs_y + y * t_sz + t_sz_side};
                  v3.pos = {map_offs_x + x * t_sz, elev01, map_offs_y + y * t_sz + t_sz_side};

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

                  SetTileGeom(rid, verts);
                  wa->GetTile(x, y)->set_rid(rid);
               }

               auto coord = Point{x, y};

               DrawGround(tile, coord);

               // auto tile_symbols =
               // std::make_shared<Tile>();
               // tile_symbols->set_mob(tile->mob());
               // tile_symbols->set_rid(rids_tile_symbols[x
               /// inc][y / inc]);
               // tile_symbols->set_tile_effect(tile->tile_effect());
               // DrawTileSymbols(tile_symbols,
               // coord);
            }
         }
      }
   }

   void WorldAddV::DrawModelsTileOutsideWorldArea(int x, int y, int dloc_x, int dloc_y) {

      auto curr_wa = World::get()->CurrWorldArea();
      auto world_loc = Hero::get()->world_location();
      auto loc = world_loc.Translate(dloc_x, dloc_y);
      auto wa = World::get()->WorldAreaAt(loc);

      if (wa) {

         if (wa->IsInsideMap({x, y})) {

            auto tile = wa->GetTile(x, y);

            if (tile) {

               auto coord = Point{x, y};

               DrawObjects(tile, coord, dloc_x, dloc_y);

               // auto tile_symbols =
               // std::make_shared<Tile>();
               // tile_symbols->set_mob(tile->mob());
               // tile_symbols->set_rid(rids_tile_symbols[x
               /// inc][y / inc]);
               // tile_symbols->set_tile_effect(tile->tile_effect());
               // DrawTileSymbols(tile_symbols,
               // coord);
            }
         }
      }
   }

   void WorldAddV::DrawGround(SharedPtr<Tile> tile, Point coord) {

      auto ground = tile->ground();

      if (ground == "GroundWater") {

         auto anim_index = ((SDL_GetTicks() + coord.x * coord.y) % 900) / 300;

         if (anim_index > 0)
            ground = "GroundWater_" + ToString(anim_index);
      }

      if (ground == "GroundGrass") {

         auto vary_index = (coord.x * coord.y) % 3;
         ground = "GroundGrass_" + ToString(vary_index);
      }

      // std::cout << ground << std::endl;
      DrawTile(ground, tile->rid());
   }

   void WorldAddV::DrawObjects(SharedPtr<Tile> tile, Point coord, int dloc_x, int dloc_y) {

      if (tile->object()) {

         auto curr_wa = World::get()->CurrWorldArea();
         auto curr_map_location = Hero::get()->world_location();
         auto tile_size = kTileSize;
         auto map_offset_x = (curr_map_location.x + dloc_x) * curr_wa->Width() * tile_size;
         auto map_offset_y = (curr_map_location.y + dloc_y) * curr_wa->Height() * tile_size;
         auto pos =
             Point3F{
                 coord.x * kTileSize,
                 CalcTileAverageElevation(coord, curr_map_location.Translate(dloc_x, dloc_y)),
                 coord.y * kTileSize}
                 .Translate(0.5f, 0.0f, 0.5f)
                 .Translate(map_offset_x, 0.0f, map_offset_y);
         auto model_rotation = 360.0f * ((coord.x * coord.y) % 10) / 10.0f;
         auto model_scaling = 0.6f * ObjectsConf::get()->GetModelScaling(tile->object()->type());
         DrawModel(
             tile->object()->type(), SDL_GetTicks() + coord.x * coord.y * 10, pos, model_rotation,
             model_scaling);
      }
   }

   void WorldAddV::DrawPlayer() {

      auto curr_wa = World::get()->CurrWorldArea();
      auto curr_map_location = Hero::get()->world_location();
      auto tile_size = kTileSize;
      auto map_offset_x = curr_map_location.x * curr_wa->Width() * tile_size;
      auto map_offset_y = curr_map_location.y * curr_wa->Height() * tile_size;
      auto player_space_coord = Hero::get()->pos().Multiply(kTileSize);
      player_space_coord.x += map_offset_x;
      player_space_coord.z += map_offset_y;
      auto player_map_coord = Hero::get()->pos().GetXZ().ToIntPoint();
      auto tile_average_elevation =
          CalcTileAverageElevation(player_map_coord, Hero::get()->world_location());
      player_space_coord.y += tile_average_elevation;
      auto ms_anim_time = 0.0f;

      if (Hero::get()->IsMoving())
         ms_anim_time = SDL_GetTicks() * 2;

      DrawModel(
          "Player2", ms_anim_time, player_space_coord, Hero::get()->facing_angle_deg() + 180.0f,
          0.6f);
   }

   void WorldAddV::DrawTileSymbols(SharedPtr<Tile> tile, Point coord) {

      auto player_pos = Hero::get()->pos().GetXZ().ToIntPoint();

      if (SDL_GetTicks() <
              Hero::get()->ticks_ulti_skill_start() + Hero::get()->ulti_skill_duration() &&
          Hero::get()->ticks_ulti_skill_start() != 0 && coord.x == player_pos.x &&
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
#endif
}
