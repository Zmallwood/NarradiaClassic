#pragma once
#include "GuiComponentView.h"

namespace Narradia {
    /**
     View component of the GuiButton.
    */
    class GuiButtonView : public GuiComponentView {
      public:
        GuiButtonView();
        void Render() override;

      private:
        RenderID rid_image;
        RenderID rid_label_text_;
    };
}
