#include "gui_window_world_map_view.h"
#include "../model/gui_window_world_map.h"
#include "core-render/view/command/new_image.h"
#include "../../core-render/view/command/draw_image.h";
namespace Narradia
{
   GuiWindowWorldMapView::GuiWindowWorldMapView() {
      gui_window_close_button_view()->set_model(
          GuiWindowWorldMap::get()->gui_window_close_button());
      rid_img_ = NewImage();
   }

   void GuiWindowWorldMapView::RenderDerived() {
       DrawImage("WorldMapImage0", rid_img_, {0.0f, 0.0f, 0.3f, 0.3f});
   }
}
