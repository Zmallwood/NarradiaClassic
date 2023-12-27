#if 1
#include "console_v.h"
#include "render-text/cmd_v/draw_string.h"
#include "render-text/cmd_v/new_string.h"
#include "render/cmd_v/draw_image.h"
#include "render/cmd_v/new_image.h"
#include "core/console.h"
#include "main_scene-gui/experience_bar.h"
#include "core.h"
#endif

namespace Narradia
{
   ConsoleV::ConsoleV()
   {
      rid_image_ = NewImage();
      rid_split_line_ = NewImage();
      rid_cmd_line_input_arrow_ = NewImage();
      rid_input_text_ = NewString();
      for (auto i = 0; i < Console::get()->MaxNumLines(); i++)
         rids_text_lines_.push_back(NewString());
   }
   void ConsoleV::Render() const
   {
      auto model = Console::get();
      if (!model->enabled())
         return;
      // Draw background image
      DrawImage("TextOutBoxBack", rid_image_, Console::get()->Bounds());
      // Draw text lines
      for (auto i = 0; i < model->MaxNumLines(); i++)
      {
         auto text_line_index = model->TextLineIndex(i);
         if (text_line_index >= 0)
         {
            PointF position = model->TextLinePosition(i);
            DrawString(
                rids_text_lines_.at(i), model->text_lines().at(text_line_index).text, position,
                model->text_lines().at(text_line_index).color);
         }
      }
      // Draw horizontal splitter
      DrawImage(
          "Wheat", rid_split_line_, model->HorizontalSplitterRect()); // Draw horizontal splitter
      if (!model->input_active())
         return;
      // Draw input arrow symbol
      DrawImage("CommandLineInputArrow", rid_cmd_line_input_arrow_, model->InputArrowRect());
      // Draw input text
      DrawString(rid_input_text_, model->InputTextWithCursor(), model->InputTextPosition());
   }
}
