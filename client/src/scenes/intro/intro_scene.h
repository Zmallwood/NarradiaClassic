#pragma once

#include "core.h"

namespace Narradia
{
   class IntroScene : public IScene, public S<IntroScene>
   {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override
      {
      }
   };
}
