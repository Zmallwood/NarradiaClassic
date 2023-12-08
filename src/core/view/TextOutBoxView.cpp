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
        auto max_num_lines = TextOutBox::Get()->GetMaxNumLines();
        for (auto i = 0; i < max_num_lines; i++)
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
        Renderer2DImagesView::Get()->DrawImage(
            "TextOutBoxBack", rid_image_, used_bounds);
        auto max_num_lines = model->GetMaxNumLines();
        for (auto i = 0; i < max_num_lines; i++) {
            auto text_line_index =
                static_cast<int>(model->text_lines().size()) - max_num_lines +
                i;
            if (text_line_index >= 0) {
                auto line_position_y =
                    used_bounds.y + (i + 1) * TextOutBox::kTextLineHeight;
                PointF position = {used_bounds.x + 0.01f, line_position_y};
                RendererText::Get()->DrawString(
                    rids_text_lines_.at(i),
                    model->text_lines().at(text_line_index).text, position,
                    model->text_lines().at(text_line_index).color);
            }
        }
        auto rect = RectF{
            0.0f,
            used_bounds.y + used_bounds.height -
                1.3f * TextOutBox::kTextLineHeight,
            TextOutBox::kBounds.width, TextOutBox::kSplitLineHeight};
        Renderer2DImagesView::Get()->DrawImage("Wheat", rid_split_line_, rect);
        if (model->input_active()) {
            auto rect_arrow = RectF{
                0.0f,
                used_bounds.y + used_bounds.height -
                    1.3f * TextOutBox::kTextLineHeight,
                TextOutBox::kTextLineHeight, TextOutBox::kTextLineHeight};
            Renderer2DImagesView::Get()->DrawImage(
                "CommandLineInputArrow", rid_cmd_line_input_arrow_, rect_arrow);
            auto position_text = rect_arrow.GetPosition().Translate(
                TextOutBox::kTextLineHeight, TextOutBox::kTextLineHeight / 2);
            auto used_text = model->input_text();
            if (SDL_GetTicks() % 600 < 300)
                used_text.insert(model->cursor_position(), "|");
            else
                used_text.insert(model->cursor_position(), " ");
            RendererText::Get()->DrawString(
                rid_input_text_, used_text, position_text);
        }
    }
}
