#pragma once

#include "core_v.h"

namespace Narradia
{
   class MainPgV : public IPageV, public S<MainPgV>
   {
     public:
      MainPgV();

     private:
      void RenderDerived() override;
   };
}
