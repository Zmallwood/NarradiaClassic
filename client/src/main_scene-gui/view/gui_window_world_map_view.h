#pragma once
#include "../../core-gui/view/gui_window_view.h"
namespace Narradia
{
   class GuiWindowWorldMapView : public GuiWindowView {
     public:
      GuiWindowWorldMapView();

      auto tex_id() {
         return tex_id_;
      }

     private:
      void RenderDerived() override;
      RenderID rid_img_;
      GLuint tex_id_ = -1;
   };
}
