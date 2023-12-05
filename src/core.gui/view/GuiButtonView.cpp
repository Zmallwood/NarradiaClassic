#include "GuiButtonView.h"
#include "core.gui/model/GuiButton.h"
#include "core.render.text/view/RendererText.h"
#include "core.render/view/Renderer2DImagesView.h"

namespace Narradia {
    GuiButtonView::GuiButtonView() {
        std::cout << "create btn view\n";
        rid_image = Renderer2DImagesView::Get()->NewImage();
        rid_label_text_ = RendererText::Get()->NewString();
    }

    void GuiButtonView::Render() {
        auto model = std::static_pointer_cast<GuiButton>(gui_component_);
        std::string_view used_image_name;
        if (model->hovered()) {
            used_image_name = model->hovered_image_name();
        }
        else {
            used_image_name = model->image_name();
        }
        auto used_bounds = model->bounds();
        //        if (p->parent_container_) {
        //            used_bounds.x += p->parent_container_->GetPosition().x;
        //            used_bounds.y += p->parent_container_->GetPosition().y;
        //        }
        Renderer2DImagesView::Get()->DrawImage(
            used_image_name, rid_image, used_bounds);
        RendererText::Get()->DrawString(
            rid_label_text_, model->text(), used_bounds.GetCenter(), Colors::wheat,
            true);
    }
}
