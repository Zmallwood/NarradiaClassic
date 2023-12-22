#include "gui_window_world_map_view.h"
#include "../model/gui_window_world_map.h"
namespace Narradia
{
   GuiWindowWorldMapView::GuiWindowWorldMapView() {
      gui_window_close_button_view()->set_model(
          GuiWindowWorldMap::get()->gui_window_close_button());
   }

   void GuiWindowWorldMapView::RenderDerived() {
   }
}
