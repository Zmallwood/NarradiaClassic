#include "gui_window_world_map_view.h"
#include "../../core-render/view/command/draw_image.h";
#include "../../core-render/view/command/draw_rect.h"
#include "../model/gui_window_world_map.h"
#include "core-render/view/command/new_image.h"
#include "core-render/view/command/new_rect.h"
#include "world-structure/model/world.h"
namespace Narradia
{
   GuiWindowWorldMapView::GuiWindowWorldMapView() {
      gui_window_close_button_view()->set_model(
          GuiWindowWorldMap::get()->gui_window_close_button());
      rid_img_ = NewImage();
      auto world_w = World::get()->world_width();
      auto world_h = World::get()->world_height();

      for (auto y = 0; y < world_h; y++) {
         for (auto x = 0; x < world_w; x++) {
            rids_rectangles_.push_back(NewRect());
            rids_images_.push_back(NewImage());
         }
      }
   }

   void GuiWindowWorldMapView::RenderDerived() {
      auto model = static_pointer_cast<GuiWindow>(gui_component_);

      auto world_w = World::get()->world_width();
      auto world_h = World::get()->world_height();
      auto bounds = model->Bounds();
      bounds.y += GuiWindow::kTitleBarHeight;
      bounds.h -= GuiWindow::kTitleBarHeight;
      auto cell_width = bounds.w / world_w;
      auto cell_height = WidthToHeight(cell_width);
      if (world_h * cell_height > bounds.h) {
         cell_height = bounds.h / world_h;
         cell_width = HeightToWidth(cell_height);
      }

      auto i = 0;
      for (auto y = 0; y < world_h; y++) {
         for (auto x = 0; x < world_w; x++) {
             DrawImage("WorldMapImage" + std::to_string(x) + "_" + std::to_string(y), rids_images_[i], {bounds.x + x * cell_width, bounds.y + y * cell_height, cell_width, cell_height});
            DrawRect(
                rids_rectangles_[i],
                {bounds.x + x * cell_width, bounds.y + y * cell_height, cell_width, cell_height},
                Colors::black);
            i++;
         }
      }
   }
}
