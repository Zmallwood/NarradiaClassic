#if 1
#include "map_gen_add.h"
#include "world_add.h"
#include "assets.h"
#include "hero.h"
#include "rend_models.h"
#include "rend_grnd.h"
#include "world.h"
#endif

namespace Narradia
{
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
            Hero::get()->set_pos({x_center, 0.0f, y_center});
            Hero::get()->set_world_location({x, y});
            auto orig_ground_fog = RendGrndV::get()->kFogColorGround;
            auto orig_objs_fog = RendModelsV::get()->kFogColorModels;
            auto width = map_area->Width();
            auto height = map_area->Height();
            auto render_dist = std::sqrt(width * width + height * height) / 2.0f;
            WorldAddV::Touch(true);
            auto a = WorldAddV::get().get();
            auto orig_render_dist = WorldAddV::get()->render_distance();
            auto orig_camera_vert_angle = Camera::get()->vertical_angle_deg();
            Camera::get()->set_vertical_angle_deg(90.0f);
            auto orig_camera_distance = Camera::get()->camera_distance();
            Camera::get()->set_camera_distance(110.0f);
            Camera::get()->UpdateGameLogic();
            WorldAddV::get()->set_render_distance(render_dist);
            RendGrndV::get()->kFogColorGround = Colors::white;
            RendModelsV::get()->kFogColorModels = Colors::white;
            WorldAddV::get()->Render();
            RendGrndV::get()->kFogColorGround = orig_ground_fog;
            RendModelsV::get()->kFogColorModels = orig_objs_fog;
            WorldAddV::get()->set_render_distance(orig_render_dist);
            Camera::get()->set_vertical_angle_deg(orig_camera_vert_angle);
            Camera::get()->set_camera_distance(orig_camera_distance);
            // GraphicsV::get()->PresentCanvas();

            ImageBank::get()->CreateBlankTextImage(
                "WorldMapImage" + std::to_string(x) + "_" + std::to_string(y));
            auto tex = ImageBank::get()->GetImage(
                "WorldMapImage" + std::to_string(x) + "_" + std::to_string(y));
            glBindTexture(GL_TEXTURE_2D, tex);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            auto canv_sz = CanvasSize();
            typedef char byte;
            byte *data = new byte[canv_sz.w * canv_sz.h * 3];
            glReadBuffer(GL_BACK);
            glReadPixels(
                canv_sz.w / 2 - canv_sz.h / 2, 0, canv_sz.h, canv_sz.h, GL_RGB, GL_UNSIGNED_BYTE,
                data);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB, canv_sz.h, canv_sz.h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glBindTexture(GL_TEXTURE_2D, 0);
            delete[] data;
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
