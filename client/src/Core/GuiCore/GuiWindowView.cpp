#include "GuiWindowView.h"
#include "Core/Rendering/ImagesRendering.h"
#include "Core/Rendering/TextRendering.h"
#include "GuiWindow.h"
#include "GuiCore.h"

namespace Narradia {
   GuiWindowV::GuiWindowV()
       : gui_window_close_button_view_(MakeShared<GuiWindowCloseButtonV>()) {
      rid_background_ = NewImage();
      rid_title_bar_ = NewImage();
      rid_title_text_ = NewString();
   }

   void GuiWindowV::Render() {
      auto model = static_pointer_cast<GuiWindow>(m_guiComponent);

      if (!model->GetVisible())
         return;

      DrawImage(model->GetBgImageName(), rid_background_, model->Bounds());
      DrawImage("GuiWindowTitleBar", rid_title_bar_, model->AbsTitleBarBounds());

      gui_window_close_button_view_->Render();

      DrawString(
          rid_title_text_, model->GetTitle(), model->Bounds().GetPosition().Translate(0.005f, 0.01f));

      RenderDerived();

      GuiMovableContainerView::Render();
   }
}
