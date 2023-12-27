#pragma once

#include "core/m/iscene.h"

namespace Narradia
{
   class MapOverviewGenScene : public IScene, public Singleton<MapOverviewGenScene>
   {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override;
   };
}
