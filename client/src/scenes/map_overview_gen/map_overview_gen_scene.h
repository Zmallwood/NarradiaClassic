#pragma once

#include "core/iscene.h"

namespace Narradia
{
   class MapOverviewGenScene : public IScene, public S<MapOverviewGenScene>
   {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override;
   };
}
