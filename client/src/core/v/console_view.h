#pragma once

#include "render-text/v/cmd/draw_string.h"
#include "render-text/v/cmd/new_string.h"
#include "render/v/cmd/draw_image.h"
#include "render/v/cmd/new_image.h"
#include "core/m/console.h"
#include "core/m/scene_mngr.h"
#include "main_scene-gui/m/experience_bar.h"

namespace Narradia
{
   class ConsoleView : public Singleton<ConsoleView>
   {
     public:
      ConsoleView();

      auto Render() const -> void;

     private:
      RenderID rid_image_;
      RenderID rid_split_line_;
      RenderID rid_cmd_line_input_arrow_;
      RenderID rid_input_text_;
      std::vector<RenderID> rids_text_lines_;
   };
}
