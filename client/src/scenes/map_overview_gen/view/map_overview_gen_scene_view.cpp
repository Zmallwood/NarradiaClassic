#include "map_overview_gen_scene_view.h"
#include "core-assets/model/image_bank.h"
#include "core-render-models/view/renderer_models_view.h"
#include "core-render/view/renderer_tiles_view.h"
#include "core/view/graphics_view.h"
#include "main_scene-modules-world_view/model/camera.h"
#include "main_scene-modules-world_view/view/world_view_module_view.h"
#include "world-actors/model/player.h"
#include "world-structure/model/world.h"
namespace Narradia
{
   void MapOverviewGenSceneView::RenderDerived() {
      auto world_width = World::get()->world_width();
      auto world_height = World::get()->world_height();
      auto map_areas = World::get()->map_areas();

      for (auto y = 0; y < world_height; y++) {
         for (auto x = 0; x < world_width; x++) {

            WorldViewModuleView::Dispose();
            RendererTilesView::Dispose();

            GraphicsView::get()->ClearCanvas();

            auto map_area = map_areas[x][y];
            auto x_center = map_area->GetWidth() / 2.0f;
            auto y_center = map_area->GetHeight() / 2.0f;
            Player::get()->set_position({x_center, 0.0f, y_center});
            Player::get()->set_world_location({x, y});
            auto orig_ground_fog = RendererTilesView::get()->kFogColorGround;
            auto orig_objs_fog = RendererModelsView::get()->kFogColorModels;
            auto width = map_area->GetWidth();
            auto height = map_area->GetHeight();
            auto render_dist = std::sqrt(width * width + height * height) / 2.0f;
            WorldViewModuleView::Touch(true);
            auto a = WorldViewModuleView::get().get();
            auto orig_render_dist = WorldViewModuleView::get()->render_distance();
            auto orig_camera_vert_angle = Camera::get()->vertical_angle_deg();
            Camera::get()->set_vertical_angle_deg(90.0f);
            auto orig_camera_distance = Camera::get()->camera_distance();
            Camera::get()->set_camera_distance(110.0f);
            Camera::get()->UpdateGameLogic();
            WorldViewModuleView::get()->set_render_distance(render_dist);
            RendererTilesView::get()->kFogColorGround = Colors::white;
            RendererModelsView::get()->kFogColorModels = Colors::white;
            WorldViewModuleView::get()->Render();
            RendererTilesView::get()->kFogColorGround = orig_ground_fog;
            RendererModelsView::get()->kFogColorModels = orig_objs_fog;
            WorldViewModuleView::get()->set_render_distance(orig_render_dist);
            Camera::get()->set_vertical_angle_deg(orig_camera_vert_angle);
            Camera::get()->set_camera_distance(orig_camera_distance);

            GraphicsView::get()->PresentCanvas();

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
            glReadBuffer(GL_FRONT);
            glReadPixels(
                canv_sz.w / 2 - canv_sz.h / 2, 0, canv_sz.h, canv_sz.h, GL_RGB, GL_UNSIGNED_BYTE,
                data);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB, canv_sz.h, canv_sz.h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glBindTexture(GL_TEXTURE_2D, 0);
            delete[] data;
            GraphicsView::get()->ClearCanvas();
            GraphicsView::get()->PresentCanvas();
            map_area->ClearAllRIDS();
         }
      }
      WorldViewModuleView::Dispose();
      RendererTilesView::Dispose();
   }
}
