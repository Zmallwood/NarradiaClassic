#pragma once

#include "RenderingCore.h"

namespace Narradia {
   class nRendColorsView : public nRendBaseView, public Singleton<nRendColorsView> {
     public:
      nRendColorsView();
      ~nRendColorsView();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
   };
}
