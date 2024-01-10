#pragma once

#include "RenderingCore.h"

namespace Narradia {
   class nRendImagesView: public nRendBaseView, public Singleton<nRendImagesView> {
     public:
      nRendImagesView();
      ~nRendImagesView();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
   };
}
