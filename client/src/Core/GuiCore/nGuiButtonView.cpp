#include "nGuiButtonView.h"
#include "Core/Rendering/ImagesRendering.h"
#include "Core/Rendering/TextRendering.h"
#include "nGuiButton.h"

namespace Narradia {
   nGuiButtonView::nGuiButtonView() {
      m_RIDImage = NewImage();
      m_RIDLabelText = NewString();
   }

   void nGuiButtonView::Render() {
      auto _model = std::static_pointer_cast<nGuiButton>(m_guiComponent);
      StringView _usedImgName;
      if (_model->Hovered()) {
         _usedImgName = _model->HoveredImgName();
      } else {
         _usedImgName = _model->ImgName();
      }
      auto _usedBounds = _model->Bounds();
      //        if (p->parent_container_) {
      //            used_bounds.x +=
      //            p->parent_container_->GetPosition().x;
      //            used_bounds.y +=
      //            p->parent_container_->GetPosition().y;
      //        }
      DrawImage(_usedImgName, m_RIDImage, _usedBounds);
      DrawString(m_RIDLabelText, _model->Text(), _usedBounds.GetCenter(), Colors::wheat, true);
   }
}
