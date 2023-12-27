#pragma once

#include "gui-core_v.h"

namespace Narradia
{
   class StatusPanelV : public GuiComponentV
   {
     public:
      StatusPanelV();
      void Render() override;

     private:
      RenderID rid_background_image_;
      RenderID rid_health_text_;
      RenderID rid_stamina_text_;
      RenderID rid_health_bar_;
      RenderID rid_health_bar_filled_;
      RenderID rid_stamina_bar_;
      RenderID rid_stamina_bar_filled_;
      RenderID rid_player_name_;
      RenderID rid_level_label_;
      RenderID rid_level_;
   };
}
