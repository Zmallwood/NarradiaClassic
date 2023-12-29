#pragma once

#include "core_c.h"

namespace Narradia
{
   class MapCreationPgC : public IPageC, public S<MapCreationPgC>
   {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}
