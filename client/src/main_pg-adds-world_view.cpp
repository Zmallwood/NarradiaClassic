#if 1
#include "main_pg-adds-world_view.h"
#include "assets.h"
#include "conf.h"
#include "render/camera_gl.h"
#include "actors.h"
#include "world-struct.h"
#include "math.h"
#endif

namespace Narradia
{
    // WorldViewModele
#if 1
   WorldViewAdd::WorldViewAdd()
   {
   }
   void WorldViewAdd::UpdateGameLogic()
   {
      Camera::get()->UpdateGameLogic();
   }
#endif

   // Camera
#if 1
   void Camera::UpdateGameLogic()
   {
      {
         auto new_perspective_matrix =
             glm::perspective(glm::radians(used_fov_ / 2), 1600.0f / 900.0f, 0.1f, 1000.0f);
         CameraGL::get()->set_perspective_matrix(new_perspective_matrix);
      }
      {
         auto player_pos = Player::get()->position().Multiply(kTileSize);
         auto curr_map_location = Player::get()->world_location();
         auto tile_size = kTileSize;
         auto map_area = World::get()->CurrWorldArea();
         auto map_offset_x = curr_map_location.x * map_area->GetWidth() * tile_size;
         auto map_offset_y = curr_map_location.y * map_area->GetHeight() * tile_size;
         auto look_from = GetCameraPosition();
         look_from = look_from.Translate(map_offset_x, 0.0f, map_offset_y);
         auto player_average_elevation =
             CalcTileAverageElevation(Player::get()->position().GetXZ().ToIntPoint());
         auto look_at = player_pos.Translate(0.0f, player_average_elevation, 0.0f);
         look_at = look_at.Translate(map_offset_x, 0.0f, map_offset_y);
         auto new_view_matrix = glm::lookAt(
             glm::vec3(look_from.x, look_from.y, look_from.z),
             glm::vec3(look_at.x, look_at.y, look_at.z), glm::vec3(0.0, 1.0, 0.0));
         CameraGL::get()->set_view_matrix(new_view_matrix);
      }
   }
   Point3F Camera::GetCameraPosition()
   {
      auto player = Player::get();
      float player_elev;
      {
         auto player_position = player->position().GetXZ();
         auto map_area = World::get()->CurrWorldArea();
         auto tile_coord = player_position.ToIntPoint();
         auto tile = map_area->GetTile(tile_coord);
         float elev00 = static_cast<float>(tile->elevation());
         float elev10 = elev00;
         float elev11 = elev00;
         float elev01 = elev00;
         {
            auto coord10 = tile_coord.Translate(1, 0);
            auto coord11 = tile_coord.Translate(1, 1);
            auto coord01 = tile_coord.Translate(0, 1);

            if (map_area->IsInsideMap(coord10))
               elev10 = map_area->GetTile(coord10)->elevation();

            if (map_area->IsInsideMap(coord11))
               elev11 = map_area->GetTile(coord11)->elevation();

            if (map_area->IsInsideMap(coord01))
               elev01 = map_area->GetTile(coord01)->elevation();
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
         auto player_position_no_elevation = player->position().Multiply(kTileSize);
         player_position_no_elevation.y = 0.0f;
         auto used_vertical_angle = vertical_angle_deg_;
         auto used_camera_distance = camera_distance_ * kTileSize;
         auto dz_unrotated = CosDeg(used_vertical_angle) * used_camera_distance;
         auto hypotenuse = dz_unrotated;
         auto dx =
             SinDeg(horizontal_angle_deg_) * hypotenuse - 3.0f * SinDeg(horizontal_angle_deg_);
         auto dz =
             CosDeg(horizontal_angle_deg_) * hypotenuse - 3.0f * CosDeg(horizontal_angle_deg_);
         auto dy = SinDeg(used_vertical_angle) * used_camera_distance * 3.0f;
         auto player_average_elevation =
             CalcTileAverageElevation(Player::get()->position().GetXZ().ToIntPoint());
         result = player_position_no_elevation.Translate(dx, dy + player_average_elevation, dz);
      }
      return result.Translate(0.0f, camera_height_ * kTileSize, 0.0f);
   }
#endif
}
