#pragma once

#include "RenderingCore.h"

namespace Narradia {
   class RendColorsView : public RendBaseV, public Singleton<RendColorsView> {
     public:
      RendColorsView();
      ~RendColorsView();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
   };
}
