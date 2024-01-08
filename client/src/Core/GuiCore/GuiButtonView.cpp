#include "GuiButtonView.h"
#include "Core/Rendering/ImagesRendering.h"
#include "Core/Rendering/TextRendering.h"
#include "GuiButton.h"

namespace Narradia {
   GuiButtonView::GuiButtonView() {
      m_RIDImage = NewImage();
      m_RIDLabelText = NewString();
   }
   void GuiButtonView::Render() {
      auto _model = std::static_pointer_cast<GuiButton>(m_guiComponent);
      StringView _usedImgName;
      if (_model->GetHovered()) {
         _usedImgName = _model->GetHoveredImgName();
      } else {
         _usedImgName = _model->GetImgName();
      }
      auto _usedBounds = _model->GetBounds();
      //        if (p->parent_container_) {
      //            used_bounds.x +=
      //            p->parent_container_->GetPosition().x;
      //            used_bounds.y +=
      //            p->parent_container_->GetPosition().y;
      //        }
      DrawImage(_usedImgName, m_RIDImage, _usedBounds);
      DrawString(m_RIDLabelText, _model->GetText(), _usedBounds.GetCenter(), Colors::wheat, true);
   }
}
