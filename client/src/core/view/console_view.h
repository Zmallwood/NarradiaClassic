#pragma once
#include "core.render.text/view/command/draw_string.h"
#include "core.render.text/view/command/new_string.h"
#include "core.render/view/command/draw_image.h"
#include "core.render/view/command/new_image.h"
#include "core/model/console.h"
#include "core/model/scene_mngr.h"
#include "main_scene.gui/model/experience_bar.h"
namespace Narradia
{
   /**
    View component of the Console.
   */
   class ConsoleView : public Singleton<ConsoleView> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Prepares RIDs for rendering.
      ////////////////////////////////////////////////////////////////////////////////
      ConsoleView();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Renders the Console with its text contents to the canvas.
      ////////////////////////////////////////////////////////////////////////////////
      auto Render() const -> void;

     private:
      RenderID rid_image_;
      RenderID rid_split_line_;
      RenderID rid_cmd_line_input_arrow_;
      RenderID rid_input_text_;
      std::vector<RenderID> rids_text_lines_;
   };
}
