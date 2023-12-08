#include "TextOutBoxView.h"
#include "core.render.text/view/RendererText.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "core/model/SceneMngr.h"
#include "core/model/TextOutBox.h"

namespace Narradia {
    /**
     * Prepares RenderIDs for rendering.
     */
    TextOutBoxView::TextOutBoxView() {
        rid_image_ = Renderer2DImagesView::Get()->NewImage();
        rid_split_line_ = Renderer2DImagesView::Get()->NewImage();
        rid_cmd_line_input_arrow_ = Renderer2DImagesView::Get()->NewImage();
        rid_input_text_ = RendererText::Get()->NewString();
        for (auto i = 0; i < TextOutBox::Get()->GetMaxNumLines(); i++)
            rids_text_lines_.push_back(RendererText::Get()->NewString());
    }

    /**
     * Renders the TextOutBox with its text content to canvas.
     */
    void TextOutBoxView::Render() const {
        auto model = TextOutBox::Get();
        if (!model->enabled())
            return;
        auto used_bounds = TextOutBox::kBounds;
        // if (SceneMngr::Get()->curr_scene() == SceneNames::Main)
        //     used_bounds =
        //         used_bounds.Translate(0.0f, -ExperienceBar::kBarHeight);
        Renderer2DImagesView::Get()->DrawImage("TextOutBoxBack", rid_image_, used_bounds);
        for (auto i = 0; i < model->GetMaxNumLines(); i++) {
            auto text_line_index = model->GetTextLineIndex(i);
            if (text_line_index >= 0) {
                PointF position = model->GetTextLinePosition(i);
                RendererText::Get()->DrawString(
                    rids_text_lines_.at(i), model->text_lines().at(text_line_index).text, position,
                    model->text_lines().at(text_line_index).color);
            }
        }
        Renderer2DImagesView::Get()->DrawImage(
            "Wheat", rid_split_line_, model->GetHorizontalSplitterRect());
        if (!model->input_active())
            return;
        Renderer2DImagesView::Get()->DrawImage(
            "CommandLineInputArrow", rid_cmd_line_input_arrow_, model->GetInputArrowRect());
        RendererText::Get()->DrawString(
            rid_input_text_, model->GetInputTextWithCursor(), model->GetInputTextPosition());
    }
}
