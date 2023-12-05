#pragma once
#include "GuiComponentView.h"

namespace Narradia {
    class GuiButtonView : public GuiComponentView {
      public:
        GuiButtonView();

        void Render() override;

      private:
        RenderId rid_image;
        RenderId rid_label_text_;
    };
}
