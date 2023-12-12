#pragma once
#include "core.gui/view/gui_component_view.h"
namespace Narradia
{
    class ExperienceBarView : public GuiComponentView {
      public:
        ExperienceBarView();
        void Render() override;
      private:
        RenderID rid_unfilled_area_;
        RenderID rid_filled_area_;
        RenderID rid_text_;
    };
}
