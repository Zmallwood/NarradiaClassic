#pragma once

#include "core.h"

namespace Narradia
{
   class MapCreationPg : public IPage, public S<MapCreationPg>
   {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override;
   };
}
