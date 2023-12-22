#pragma once
#include "../../core-gui/view/gui_window_view.h"
namespace Narradia
{
   class GuiWindowWorldMapView : public GuiWindowView {
     public:
      GuiWindowWorldMapView();

     private:
      void RenderDerived() override;
   };
}
