#include "WorldViewModuleView.h"
#include "configuration/model/Configuration.h"
#include "core.render/view/CameraGL.h"
#include "core.render/view/RendererTilesView.h"
#include "functions/DoDrawGround.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"

namespace Narradia {
    WorldViewModuleView::WorldViewModuleView() {
        auto map_area = World::Get()->curr_map_area();
        auto tile_size = 1.0f;

        for (auto x = 0; x < kMapWidth; x++) {
            rids_tiles.push_back(std::vector<RenderId>());
            for (auto y = 0; y < kMapHeight; y++) {
                rids_tiles.at(x).push_back(RendererTilesView::Get()->NewTile());

                Vertex3F v0;
                Vertex3F v1;
                Vertex3F v2;
                Vertex3F v3;

                v0.position = {x * tile_size, -1.0f, y * tile_size};
                v1.position = {x * tile_size + tile_size, -1.0f, y * tile_size};
                v2.position = {
                    x * tile_size + tile_size, -1.0f,
                    y * tile_size + tile_size};
                v3.position = {x * tile_size, -1.0f, y * tile_size + tile_size};

                v0.uv = {0.0f, 0.0f};
                v1.uv = {1.0f, 0.0f};
                v2.uv = {1.0f, 1.0f};
                v3.uv = {0.0f, 1.0f};

                Point3F normal00 = {0.0f, 1.f, 0.0f};
                Point3F normal10 = {0.0f, 1.f, 0.0f};
                Point3F normal11 = {0.0f, 1.f, 0.0f};
                Point3F normal01 = {0.0f, 1.f, 0.0f};

                RendererTilesView::Get()->SetGeometryTile(
                    rids_tiles[x][y], v0, v1, v2, v3, normal00, normal10,
                    normal11, normal01);

                map_area->GetTile(x, y)->set_rid(rids_tiles[x][y]);
            }
        }
    }

    void WorldViewModuleView::Render() {
        auto map_area = World::Get()->curr_map_area();
        auto player_pos = Player::Get()->position_3d();
        auto r = 21;

        auto used_fov = 100.0f;

        auto look_from = Point3F{kMapWidth / 2.0f, 1.0f, kMapHeight / 2.0f};
        auto look_at = Point3F{0.0f, 0.0f, 0.0f};

        auto new_perspective_matrix = glm::perspective(
            glm::radians(used_fov / 2), 1600.0f / 900.0f, 0.1f, 1000.0f);
        auto new_view_matrix = glm::lookAt(
            glm::vec3(look_from.x, look_from.y, look_from.z),
            glm::vec3(look_at.x, look_at.y, look_at.z),
            glm::vec3(0.0, 1.0, 0.0));

        CameraGL::Get()->set_perspective_matrix(new_perspective_matrix);
        CameraGL::Get()->set_view_matrix(new_view_matrix);

        auto x_center = static_cast<int>(player_pos.x);
        auto y_center = static_cast<int>(player_pos.z);

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
                DoDrawGround(tile, coord);
            }
        }
    }
}
