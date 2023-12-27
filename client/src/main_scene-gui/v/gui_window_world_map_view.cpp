#if 1
#include "gui_window_world_map_view.h"
#include "render/v/cmd/draw_image.h"
#include "render/v/cmd/draw_rect.h"
#include "render/v/cmd/fill_rect.h"
#include "main_scene-gui/m/gui_window_world_map.h"
#include "render/v/cmd/new_image.h"
#include "render/v/cmd/new_rect.h"
#include "world-actors/m/player.h"
#include "world-struct/m/world.h"
#include "gui-core/v/gui_window_close_button_view.h"
#include "world-struct/m/map_area.h"
#endif

namespace Narradia
{
   GuiWindowWorldMapView::GuiWindowWorldMapView()
   {
      gui_window_close_button_view()->set_model(
          GuiWindowWorldMap::get()->gui_window_close_button());
      rid_img_ = NewImage();
      auto world_w = World::get()->world_width();
      auto world_h = World::get()->world_height();

      for (auto y = 0; y < world_h; y++)
      {
         for (auto x = 0; x < world_w; x++)
         {
            rids_rectangles_.push_back(NewRect());
            rids_images_.push_back(NewImage());
         }
      }

      rid_player_ = NewRect();
      rid_player_outline_ = NewRect();
   }

   void GuiWindowWorldMapView::RenderDerived()
   {
      auto model = static_pointer_cast<GuiWindow>(gui_component_);

      auto world_w = World::get()->world_width();
      auto world_h = World::get()->world_height();
      auto bounds = model->Bounds();
      bounds.y += GuiWindow::kTitleBarHeight + GuiWindow::kMargin;
      bounds.h -= GuiWindow::kTitleBarHeight + 3 * GuiWindow::kMargin;
      auto cell_width = bounds.w / world_w;
      auto cell_height = WidthToHeight(cell_width);
      if (world_h * cell_height > bounds.h)
      {
         cell_height = bounds.h / world_h;
         cell_width = HeightToWidth(cell_height);
      }

      auto i = 0;
      for (auto y = 0; y < world_h; y++)
      {
         for (auto x = 0; x < world_w; x++)
         {
            DrawImage(
                "WorldMapImage" + std::to_string(x) + "_" + std::to_string(y), rids_images_[i],
                {bounds.x + x * cell_width, bounds.y + y * cell_height, cell_width, cell_height});
            DrawRect(
                rids_rectangles_[i],
                {bounds.x + x * cell_width, bounds.y + y * cell_height, cell_width, cell_height},
                Colors::black);
            if (x == Player::get()->world_location().x && y == Player::get()->world_location().y)
            {
               auto player_pos = Player::get()->position();
               auto map_area = World::get()->map_areas()[x][y];
               auto tile_width = cell_width / map_area->GetWidth();
               auto tile_height = cell_height / map_area->GetHeight();
               auto marker_size = 0.005f;
               auto rect = RectF{
                   bounds.x + x * cell_width + player_pos.x * tile_width,
                   bounds.y + y * cell_height + player_pos.z * tile_height, marker_size,
                   marker_size};
               FillRect(rid_player_, rect, Colors::red);
               DrawRect(rid_player_outline_, rect, Colors::black);
            }
            i++;
         }
      }
   }
}
