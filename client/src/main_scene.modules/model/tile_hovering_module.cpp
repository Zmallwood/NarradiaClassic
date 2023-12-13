#include "tile_hovering_module.h"
#include "conf/model/conf.h"
#include "core.render/view/camera_gl.h"
#include "world.actors/model/player.h"
#include "world.structure/model/world.h"
namespace Narradia
{
    void TileHoveringModule::UpdateGameLogic() {
        auto view_matrix = CameraGL::get()->view_matrix();
        auto perspective_matrix = CameraGL::get()->perspective_matrix();
        auto mouse_position_f = GetMousePosition();
        auto canvas_size = GetCanvasSize();
        auto player_x = Player::get()->position().x;
        auto player_y = Player::get()->position().z;
        auto tile_size = kTileSize;
        auto elev_amount = kElevAmount;
        auto player_world_area_position = Player::get()->position().Multiply(kTileSize);
        auto map_area = World::get()->curr_map_area();
        auto mouse_world_near_plane = glm::unProject(
            glm::vec3(
                mouse_position_f.x * canvas_size.w,
                (1.0f - mouse_position_f.y) * canvas_size.h, 0.0f),
            view_matrix, perspective_matrix,
            glm::ivec4(0, 0, canvas_size.w, canvas_size.h));
        auto mouse_world_far_plane = glm::unProject(
            glm::vec3(
                mouse_position_f.x * canvas_size.w,
                (1.0f - mouse_position_f.y) * canvas_size.h, 1.0f),
            view_matrix, perspective_matrix,
            glm::ivec4(0, 0, canvas_size.w, canvas_size.h));
        auto columns_count = 111;
        auto rows_count = 111;
        auto player_x_major = static_cast<int>(player_x);
        auto player_y_major = static_cast<int>(player_y);
        bool tile_found = false;
        auto fn_iteration = [&](int x, int y) -> bool {
            auto map_x = player_x_major + x;
            auto map_y = player_y_major + y;
            if (!map_area->IsInsideMap({map_x, map_y}))
                return false;
            auto tile_coord = Point{map_x, map_y};
            auto tile = map_area->GetTile(tile_coord);
            auto elev00 = static_cast<float>(tile->elevation());
            auto elev10 = elev00;
            auto elev11 = elev00;
            auto elev01 = elev00;
            auto tile_avg_elev = (elev00 + elev10 + elev01 + elev11) / 4.0f;
            auto coord10 = tile_coord.Translate(1, 0);
            auto coord11 = tile_coord.Translate(1, 1);
            auto coord01 = tile_coord.Translate(0, 1);
            if (map_area->IsInsideMap(coord10))
                elev10 = map_area->GetTile(coord10)->elevation();
            if (map_area->IsInsideMap(coord11))
                elev11 = map_area->GetTile(coord11)->elevation();
            if (map_area->IsInsideMap(coord01))
                elev01 = map_area->GetTile(coord01)->elevation();
            auto x0 = tile_coord.x * tile_size;
            auto y0 = elev00 * elev_amount;
            auto z0 = tile_coord.y * tile_size;
            auto x2 = tile_coord.x * tile_size + tile_size;
            auto y2 = elev11 * elev_amount;
            auto z2 = tile_coord.y * tile_size + tile_size;
            auto center = glm::vec3{(x0 + x2) / 2, (y0 + y2) / 2, (z0 + z2) / 2};
            auto closest_point =
                glm::closestPointOnLine(center, mouse_world_near_plane, mouse_world_far_plane);
            if (glm::distance(center, closest_point) < tile_size / 2) {
                hovered_tile_ = {map_x, map_y};
                tile_found = true;
                return true;
            }
            return false;
        };
        for (int y = -(rows_count - 1) / 2; y < (rows_count - 1) / 2 && !tile_found; y++) {
            for (int x = -(columns_count - 1) / 2; x < (columns_count - 1) / 2 && !tile_found;
                 x++) {
                if (fn_iteration(x, y))
                    return;
            }
        }
    }
}
