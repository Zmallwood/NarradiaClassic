#pragma once

#include "core_c.h"

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
