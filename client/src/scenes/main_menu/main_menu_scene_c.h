#pragma once

#include "core/iscene_c.h"

namespace Narradia
{
   class MainMenuSceneC : public ISceneC, public S<MainMenuSceneC>
   {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}
