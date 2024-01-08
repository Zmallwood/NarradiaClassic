#pragma once

#include "GuiContainerView.h"

namespace Narradia {
   class GuiMovableContainerView : public GuiContainerView {
     protected:
      void Render() override;
   };
}
