#pragma once

#include "core_v.h"

namespace Narradia
{
   class MapCreationPgV : public IPageV, public S<MapCreationPgV>
   {
     private:
      void RenderDerived() override;
   };
}
