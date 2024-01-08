#pragma once

#include "RenderingCore.h"

namespace Narradia {
   class RendImagesView: public RendBaseV, public Singleton<RendImagesView> {
     public:
      RendImagesView();
      ~RendImagesView();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
   };
}
