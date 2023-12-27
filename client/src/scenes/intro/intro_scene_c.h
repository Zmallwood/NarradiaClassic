#pragma once

#include "core_c.h"

namespace Narradia
{
   class IntroSceneC : public ISceneC, public S<IntroSceneC>
   {
     private:
      void OnEnter() override;
      void UpdateGameFlowDerived() override;
   };
}
