#pragma once

#include "core/iscene_c.h"

namespace Narradia
{
   class MainSceneC : public ISceneC, public S<MainSceneC>
   {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}
