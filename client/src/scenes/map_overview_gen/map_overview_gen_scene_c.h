#pragma once

#include "core_c.h"

namespace Narradia
{
   class MapOverViewGenSceneC : public ISceneC, public S<MapOverViewGenSceneC>
   {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}
