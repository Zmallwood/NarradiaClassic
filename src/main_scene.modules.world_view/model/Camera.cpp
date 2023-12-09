#include "Camera.h"
#include "conf/model/Configuration.h"
#include "core.render/view/CameraGL.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"

namespace Narradia {
    void Camera::UpdateGameLogic() {
        {
            auto new_perspective_matrix =
                glm::perspective(glm::radians(used_fov_ / 2), 1600.0f / 900.0f, 0.1f, 1000.0f);
            CameraGL::Get()->set_perspective_matrix(new_perspective_matrix);
        }
        {
            auto player_pos = Player::Get()->position();
            auto look_from = GetCameraPosition();
            auto look_at = player_pos.Translate(0.0f, camera_height_ * kTileSize, 0.0f);
            auto new_view_matrix = glm::lookAt(
                glm::vec3(look_from.x, look_from.y, look_from.z),
                glm::vec3(look_at.x, look_at.y, look_at.z), glm::vec3(0.0, 1.0, 0.0));
            CameraGL::Get()->set_view_matrix(new_view_matrix);
        }
    }

    Point3F Camera::GetCameraPosition() {
        auto player = Player::Get();
        auto player_position = player->position().GetXZ();
        auto map_area = World::Get()->curr_map_area();
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

        float player_elev;
        {
            auto tile_avg_elev = (elev00 + elev10 + elev01 + elev11) / 4.0f;
            auto player_tile_dx = player_position.x - static_cast<int>(player_position.x) - 0.5f;
            auto player_tile_dy = player_position.y - static_cast<int>(player_position.y) - 0.5f;
            auto elev_dx = ((elev10 - elev00) + (elev11 - elev01)) / 2.0f;
            auto elev_dy = ((elev01 - elev00) + (elev11 - elev10)) / 2.0f;
            player_elev = tile_avg_elev + player_tile_dx * elev_dx + player_tile_dy * elev_dy;
        }

        Point3F result;
        {
            auto elev_amount = kElevAmount;
            auto player_position_no_elevation = player->position().Multiply(kTileSize);
            auto used_vertical_angle = vertical_angle_deg_;
            auto used_camera_distance = camera_distance_ * kTileSize;
            auto dz_unrotated = CosDeg(used_vertical_angle) * used_camera_distance;
            auto hypotenuse = dz_unrotated;
            auto dx =
                SinDeg(horizontal_angle_deg_) * hypotenuse - 3.0f * SinDeg(horizontal_angle_deg_);
            auto dz =
                CosDeg(horizontal_angle_deg_) * hypotenuse - 3.0f * CosDeg(horizontal_angle_deg_);
            auto dy = SinDeg(used_vertical_angle) * used_camera_distance;
            result = player_position_no_elevation.Translate(dx, dy + player_elev * elev_amount, dz);
        }

        return result.Translate(0.0f, camera_height_ * kTileSize, 0.0f);
    }
}
