#pragma once

#include "gui-core/gui_window_v.h"

namespace Narradia
{
   class GuiWindowWorldMapV : public GuiWindowV
   {
     public:
      GuiWindowWorldMapV();
      auto tex_id()
      {
         return tex_id_;
      }

     private:
      void RenderDerived() override;
      RenderID rid_img_;
      GLuint tex_id_ = -1;
      std::vector<RenderID> rids_rectangles_;
      std::vector<RenderID> rids_images_;
      RenderID rid_player_;
      RenderID rid_player_outline_;
   };
}
