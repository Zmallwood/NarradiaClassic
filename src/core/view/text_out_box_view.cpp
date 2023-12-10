#include "text_out_box_view.h"
#include "core.render.text/view/command/draw_string.h"
#include "core.render.text/view/command/new_string.h"
#include "core.render/view/command/draw_image.h"
#include "core.render/view/command/new_image.h"
#include "core/model/text_out_box.h"
namespace Narradia {
  /**
   Prepares RenderIDs for rendering.
  */
  TextOutBoxView::TextOutBoxView() {
    rid_image_ = NewImage();
    rid_split_line_ = NewImage();
    rid_cmd_line_input_arrow_ = NewImage();
    rid_input_text_ = NewString();
    for (auto i = 0; i < TextOutBox::Get()->GetMaxNumLines(); i++)
      rids_text_lines_.push_back(NewString());
  }

  /**
   Renders the TextOutBox with its text content to canvas.
  */
  void TextOutBoxView::Render() const {
    auto model = TextOutBox::Get();
    if (!model->enabled())
      return;
    auto used_bounds = TextOutBox::kBounds;
    // if (SceneMngr::Get()->curr_scene() ==
    // SceneNames::Main)
    //     used_bounds =
    //         used_bounds.Translate(0.0f,
    //         -ExperienceBar::kBarHeight);
    DrawImage("TextOutBoxBack", rid_image_, used_bounds);
    for (auto i = 0; i < model->GetMaxNumLines(); i++) {
      auto text_line_index = model->GetTextLineIndex(i);
      if (text_line_index >= 0) {
        PointF position = model->GetTextLinePosition(i);
        DrawString(
            rids_text_lines_.at(i), model->text_lines().at(text_line_index).text, position,
            model->text_lines().at(text_line_index).color);
      }
    }
    DrawImage("Wheat", rid_split_line_, model->GetHorizontalSplitterRect());
    if (!model->input_active())
      return;
    DrawImage("CommandLineInputArrow", rid_cmd_line_input_arrow_, model->GetInputArrowRect());
    DrawString(rid_input_text_, model->GetInputTextWithCursor(), model->GetInputTextPosition());
  }
}
