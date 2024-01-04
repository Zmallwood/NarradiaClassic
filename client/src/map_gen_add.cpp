#if 1
#include "map_gen_add.h"
#include "assets.h"
#include "hero.h"
#include "rend_grnd.h"
#include "rend_models.h"
#include "world.h"
#include "world_add.h"
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
            Camera::get()->set_camera_distance(110.0f*2.0f);
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
            // byte *data = new byte[canv_sz.w * canv_sz.h * 3];
            int w = canv_sz.h;
            int h = canv_sz.h;
            std::vector<uint8_t> pixels(3 * w * h);
            //glReadPixels(x, y, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

            glReadBuffer(GL_BACK);
            glReadPixels(
                canv_sz.w / 2 - canv_sz.h / 2, 0, canv_sz.h, canv_sz.h, GL_RGB, GL_UNSIGNED_BYTE,
                pixels.data());
            for (int line = 0; line < h; line++) {
               for (auto px = 0; px < w / 2; px++) {
                  for (auto val = 0; val < 3; val++) {
                     auto pos1 = line*w*3+px*3 + val;
                     auto pos2 = line*w*3 + w*3 - px*3 + val;
                     //if (pos1 < 0 || pos1 >= 3*w*h) {
                     //   std::cout << "error pos 1\n";
                     //   continue;
                     //}
                     //if (pos2 < 0 || pos2 >= 3*w*h) {
                     //   std::cout << "error pos 2\n";
                     //   continue;
                     //}
                     
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
