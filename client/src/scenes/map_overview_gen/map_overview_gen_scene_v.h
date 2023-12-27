#pragma once

#include "core/iscene_v.h"

namespace Narradia
{
   class MapOverviewGenSceneV : public ISceneV, public S<MapOverviewGenSceneV>
   {
     private:
      void RenderDerived() override;
   };
}
