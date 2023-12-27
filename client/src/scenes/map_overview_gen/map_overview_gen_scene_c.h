#pragma once

#include "core/iscene_c.h"

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
