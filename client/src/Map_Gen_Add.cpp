#include "Map_Gen_Add.h"
#include "Engine/Assets/Assets.h"
#include "Engine/Rendering/Ground_Rendering.h"
#include "Engine/Rendering/Models_Rendering.h"
#include "World_Add.h"
#include "World_Structure/Actors/Player.h"
#include "World_Structure/World_Structure.h"

namespace Narradia {

    // View

#if 1
    void MapGenAddV::Render() {
        auto world_width = World::get()->world_width();
        auto world_height = World::get()->world_height();
        auto map_areas = World::get()->world_areas();

        for (auto y = 0; y < world_height; y++) {
            for (auto x = 0; x < world_width; x++) {
                WorldAddV::Dispose();
                RendGrndV::Dispose();

                GraphicsV::get()->ClearCanvas();

                auto map_area = map_areas[x][y];
                auto x_center = map_area->Width() / 2.0f;
                auto y_center = map_area->Height() / 2.0f;
                Player::get()->set_pos({x_center, 0.0f, y_center});
                Player::get()->set_world_location({x, y});
                auto orig_ground_fog = RendGrndV::get()->fog_color_ground();
                auto orig_objs_fog = RendModelsV::get()->fog_color_models();
                auto width = map_area->Width();
                auto height = map_area->Height();
                auto render_dist = std::sqrt(width * width + height * height) / 2.0f;
                WorldAddV::Touch(true);
                auto a = WorldAddV::get().get();
                auto orig_render_dist = WorldAddV::get()->render_distance();
                auto orig_camera_vert_angle = Camera::get()->vertical_angle_deg();
                Camera::get()->set_use_fixed_camera_distance(true);
                Camera::get()->set_vertical_angle_deg(90.0f);
                Camera::get()->UpdateGameLogic();
                WorldAddV::get()->set_render_distance(render_dist);
                RendGrndV::get()->set_fog_color_ground(Colors::white);
                RendModelsV::get()->set_fog_color_models(Colors::white);
                WorldAddV::get()->Render();
                Camera::get()->set_use_fixed_camera_distance(false);
                RendGrndV::get()->set_fog_color_ground(orig_ground_fog);
                RendModelsV::get()->set_fog_color_models(orig_objs_fog);
                WorldAddV::get()->set_render_distance(orig_render_dist);
                Camera::get()->set_vertical_angle_deg(orig_camera_vert_angle);
                // GraphicsV::get()->PresentCanvas();

                ImageBank::get()->CreateBlankTextImage(
                    "WorldMapImage" + To_String(x) + "_" + To_String(y));
                auto tex =
                    ImageBank::get()->GetImage("WorldMapImage" + To_String(x) + "_" + To_String(y));
                glBindTexture(GL_TEXTURE_2D, tex);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                auto canv_sz = Get_Canvas_Size();
                typedef char byte;
                // byte *data = new byte[canv_sz.w * canv_sz.h * 3];
                int w = canv_sz.h;
                int h = canv_sz.h;
                Vector<uint8_t> pixels(3 * w * h);
                // glReadPixels(x, y, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

                glReadBuffer(GL_BACK);
                glReadPixels(
                    canv_sz.w / 2 - canv_sz.h / 2, 0, canv_sz.h, canv_sz.h, GL_RGB,
                    GL_UNSIGNED_BYTE, pixels.data());

                for (int line = 0; line < h; line++) {
                    for (auto px = 0; px < w / 2; px++) {
                        for (auto val = 0; val < 3; val++) {
                            auto pos1 = line * w * 3 + px * 3 + val;
                            auto pos2 = line * w * 3 + w * 3 - px * 3 + val;
                            // if (pos1 < 0 || pos1 >= 3*w*h) {
                            //    std::cout << "error pos 1\n";
                            //    continue;
                            // }
                            // if (pos2 < 0 || pos2 >= 3*w*h) {
                            //    std::cout << "error pos 2\n";
                            //    continue;
                            // }

                            auto &a = pixels.data()[pos1];
                            auto &b = pixels.data()[pos2];
                            std::swap(a, b);
                        }
                    }
                }

                glTexImage2D(
                    GL_TEXTURE_2D, 0, GL_RGB, canv_sz.h, canv_sz.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                    pixels.data());
                glBindTexture(GL_TEXTURE_2D, 0);
                // delete[] data;
                GraphicsV::get()->ClearCanvas();
                // GraphicsV::get()->PresentCanvas();
                map_area->ClearAllRIDs();
            }
        }

        WorldAddV::Dispose();
        RendGrndV::Dispose();
    }
#endif

}