#include "Camera.h"
#include "configuration/model/Configuration.h"
#include "core.render/view/CameraGL.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"

namespace Narradia
{
    void Camera::UpdateGameLogic()
    {
        auto player_pos = Player::Get()->position();
        auto look_from = GetCameraPosition();
        auto look_at = player_pos;
        auto new_perspective_matrix =
            glm::perspective(glm::radians(used_fov_ / 2), 1600.0f / 900.0f, 0.1f, 1000.0f);
        auto new_view_matrix = glm::lookAt(
            glm::vec3(look_from.x, look_from.y, look_from.z),
            glm::vec3(look_at.x, look_at.y, look_at.z), glm::vec3(0.0, 1.0, 0.0));
        CameraGL::Get()->set_perspective_matrix(new_perspective_matrix);
        CameraGL::Get()->set_view_matrix(new_view_matrix);
    }

    Point3F Camera::GetCameraPosition()
    {
        std::shared_ptr<Player> player = Player::Get();
        std::shared_ptr<World> world = World::Get();
        float used_camera_distance = camera_distance_;
        float used_vertical_angle = vertical_angle_deg_;
        Point3F player_position_no_elevation = player->position().Multiply(kTileSize);
        float dz_unrotated = CosDeg(used_vertical_angle) * used_camera_distance;
        float hypotenuse = dz_unrotated;
        float dx =
            SinDeg(horizontal_angle_deg_) * hypotenuse - 3.0f * SinDeg(horizontal_angle_deg_);
        float dz =
            CosDeg(horizontal_angle_deg_) * hypotenuse - 3.0f * CosDeg(horizontal_angle_deg_);
        float dy = SinDeg(used_vertical_angle) * used_camera_distance;
        float dx_player = -4.0f * SinDeg(horizontal_angle_deg_);
        float dz_player = -4.0f * CosDeg(horizontal_angle_deg_);
        PointF player_position = player->position().GetXZ();
        std::shared_ptr<MapArea> map_area = World::Get()->curr_map_area();
        std::shared_ptr<Tile> player_tile = map_area->GetTile(player_position.ToIntPoint());
        float elev_amount = kElevAmount;
        Point tile_coord = player_position.ToIntPoint();
        std::shared_ptr<Tile> tile = map_area->GetTile(tile_coord);
        float elev00 = static_cast<float>(tile->elevation());
        float elev10 = elev00;
        float elev11 = elev00;
        float elev01 = elev00;
        Point coord10 = tile_coord.Translate(1, 0);
        Point coord11 = tile_coord.Translate(1, 1);
        Point coord01 = tile_coord.Translate(0, 1);

        if (map_area->IsInsideMap(coord10))
            elev10 = map_area->GetTile(coord10)->elevation();

        if (map_area->IsInsideMap(coord11))
            elev11 = map_area->GetTile(coord11)->elevation();

        if (map_area->IsInsideMap(coord01))
            elev01 = map_area->GetTile(coord01)->elevation();

        float tile_avg_elev = (elev00 + elev10 + elev01 + elev11) / 4.0f;
        float player_tile_dx = player_position.x - static_cast<int>(player_position.x) - 0.5f;
        float player_tile_dy = player_position.y - static_cast<int>(player_position.y) - 0.5f;
        float elev_dx = ((elev10 - elev00) + (elev11 - elev01)) / 2.0f;
        float elev_dy = ((elev01 - elev00) + (elev11 - elev10)) / 2.0f;
        float player_elev = tile_avg_elev + player_tile_dx * elev_dx + player_tile_dy * elev_dy;

        return player_position_no_elevation.Translate(dx, dy + player_elev * elev_amount, dz);
    }
}
